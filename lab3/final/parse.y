 %polymorphic INT: int ; FLOAT: float; TEXT: std::string; ABS: abstract_astnode*; STMT: StmtAst*; EXP: ExpAst*; EXPGP: EXP_GROUP*; SYMTAB: SymTab *; SYMROW: SymRow*; VECSYMROW: std::vector<SymRow*> ; FNDATA: std::pair<SymTab *, abstract_astnode *>; TYPEPAIR: std::pair<string,int>;
%scanner Scanner.h
%scanner-token-function d_scanner.lex()
%type <ABS> translation_unit, struct_specifier, function_definition, compound_statement
%type <STMT> statement, statement_list, assignment_statement, selection_statement, iteration_statement
%type <EXP> expression, logical_and_expression, equality_expression, relational_expression, additive_expression, multiplicative_expression
%type <EXP> unary_expression, postfix_expression, primary_expression, logical_or_expression
%type <EXPGP> expression_list;
%type <TEXT> unary_operator, IDENTIFIER
%type <TYPEPAIR> type_specifier
%type <SYMROW> fun_declarator, declarator;
%type <VECSYMROW> declarator_list 

%token FLOAT INT INT_CONSTANT VOID FLOAT_CONSTANT
%token IF ELSE WHILE FOR RETURN
%token LE_OP GE_OP NE_OP EQ_OP AND_OP OR_OP INC_OP
%token OTHERS STRING_LITERAL STRUCT PTR_OP



%%
print_symtabs_and_ast :
    translation_unit
    {
        print_symtab_ast(); 	// print symbol tables in output file: symtables.csv
        // $1->print();        	// print AST tree in stdout
        // $1->generate_code(1);   // generate_code
    }
;


translation_unit :  
    struct_specifier
    { 
        abstract_astnode *a = new AST_EMPTY();
        abstract_astnode *b = new AST_GROUP();
        b->pushAST(a);
        $$ = b;
    } 
 	| function_definition 
    {
        abstract_astnode *f = $1;
        abstract_astnode *b = new AST_GROUP();
        b->pushAST(f);
        $$ = b;
    } 
 	| translation_unit function_definition
    {
        abstract_astnode *f = $2;
        $1->pushAST(f);
        $$ = $1;
    }  
    | translation_unit struct_specifier
    { 
        abstract_astnode *a = new AST_EMPTY();
        $1->pushAST(a);
        $$ = $1;
    } 
;

struct_specifier : 
    STRUCT IDENTIFIER '{' declaration_list '}' ';'
    {
        line_num = d_scanner.lineNr();
        SymRow * a = new SymRow();
        a->symName = $2;
        a->var_fun = 2;     				//since struct
        a->head = NULL;     				//struct has no type
        a->tail = NULL;
        a->param_local = -1;
        a->symTab = localSymTab;

        //find size of struct
        a->size = 0;
        map<string, SymRow *> :: iterator beg = localSymTab->sym_rows.begin();
        while(beg != localSymTab->sym_rows.end()){		//sum of all attribute sizes
            a->size += (beg->second)->size;
            beg++;
        }
        int err = globalSymTab->insertRow("struct " + a->symName, a);
        if(err == -1){
            print_error(-1, "");						//print_error exits the parser.
        }
        localSymTab = new SymTab();
        para_index = 1;
        global_offset = 0;
        ret_type = "";
        curr_fn = "";
    }
;

function_definition : 
    type_specifier fun_declarator
    {
        line_num = d_scanner.lineNr();
        SymRow * a = $2;
        a->size = get_base_size(a->tail);
    } 
    compound_statement 
    {
        line_num = d_scanner.lineNr();
        SymRow * a = $2;
        std::pair<string,int> dec_type = $1;
        
        // the entire code of the function is printed over here; we have the compount statement 
        // currently localSymTable points to the sym table of the current function
        int local_stack = generate_code_fn_init(a->symName);
        next_label_stack.push(label_count);
        label_count++;
        $4->generate_code(1);
        cout << "$L" << next_label_stack.top() << ":" << endl;
        next_label_stack.pop();                 // restpring the label stack
        generate_code_fn_end(local_stack);      // code geerated at end of function

        // resetting variables for the next function/Struct to come
        localSymTab = new SymTab();             
        para_index = 1;
        global_offset = 0;
        ret_type = "";                          // resetting the return type and curr function name
        curr_fn = "";

        $$ = $4;
    }
;

type_specifier :  
    VOID 
    { 
        string a = "void";
        if(ret_type == "")
          ret_type = "void"; 

        int t_size = 1;
        $$ = make_pair(a, t_size);
    }   
    | INT   
    {
        string a = "int";
        if(ret_type == "")
            ret_type = "int";

        int t_size = 4;
        $$ = make_pair(a, t_size);
    } 
    | FLOAT 
    {
        string a = "float";
        if(ret_type == "")
            ret_type = "float";

        int t_size = 4;
        $$ = make_pair(a, t_size);
    } 
    | STRUCT IDENTIFIER 
    {
        string struct_name = $2;
        if(ret_type == "")
            ret_type = "struct " + struct_name;
        int t_size = 1;
        $$ = make_pair("struct "+ struct_name, t_size); 
    } 
;

fun_declarator: 
    IDENTIFIER '(' parameter_list ')' 
    {
        line_num = d_scanner.lineNr();
        SymRow * a = new SymRow();
        a->head = a->tail = new var_type(ret_type);
        a->symName = $1;
        a->var_fun = 1;
        a->param_local = -1;
        a->symTab = localSymTab;
        global_offset = -4;      					//set to -4 due to return address of 4 bytes.
        
        // add function to global sym table for recursive calling
        int err = globalSymTab->insertRow(a->symName, a);

        if(err == -1){
            print_error(-1, "");
        }
        curr_fn = a->symName; 						//setting the curr function name;
        //generate_code_fn_init(a->symName);               //generates initialization  code of function (implemented as an independent function as there is no ExpAst for function definitions.)
        $$ = a; 
    }
    | IDENTIFIER '(' ')'
    {
        line_num = d_scanner.lineNr();
        SymRow * a = new SymRow();
        a->head = a->tail = new var_type(ret_type);
        a->symName = $1;
        a->var_fun = 1;
        a->param_local = -1;
        a->symTab = localSymTab;
        global_offset = -4;      					//set to -4 due to return address of 4 bytes.
        
        // add it to global sym table for recursive calling
        int err = globalSymTab->insertRow(a->symName, a);

        if(err == -1){
            print_error(-1, "");
        }
        curr_fn = a->symName;						//setting the curr function name;
        //generate_code_fn_init(a->symName);               //generates initialization  code of function (implemented as an independent function as there is no ExpAst for function definitions.)
        $$ = a; 
    }
    | '*' fun_declarator  
    {
        SymRow * a = $2;
        ret_type = ret_type+"*";
        (a->head)->t = (a->head)->t + "*";
        a->tail = a->head;
        $$ = a;    
    } 
	;

parameter_list: 
    parameter_declaration 
	{
    }
    | parameter_list ',' parameter_declaration 
    {
    }
;

parameter_declaration: 
    type_specifier declarator 
    {
        line_num = d_scanner.lineNr();
        std::pair<string,int> dec_type = $1;
        SymRow * dec = $2;
        
        // updating the type
        if(dec->head == NULL){
            var_type *tp = new var_type(dec_type.first);
            dec->head = dec->tail = tp;
        }
        else{
            if((dec->tail)->t[0] == '*'){    				//if already a pointer.
                (dec->tail)->t = dec_type.first + (dec->tail)->t;
            }
            else{
                var_type *tp = new var_type(dec_type.first);
                (dec->tail)->type = tp;
                dec->tail = tp;
            }
        }
        
        //calculate size
        // int base_size = get_base_size(dec->tail);
        // parameter are either
        // pointer size 4
        // int/float size 4
        // arays size 4
        // structs size varies
        string type = get_type(dec->head, "");
        if((type.substr(0,6) == "struct") && (rem_base_type(type) == "")){
            dec->size = get_base_size(dec->head);
        }
        else{
            dec->size = 4;
        }

        if(get_type(dec->tail, "") == "void"){      //check only tail as declaration like void v[10] is not allowed.
            print_error(-2, "");                    //error if variable declared as void
        }
        
        else{
            dec->offset = global_offset + dec->size + 4; // need to move parameters up by 1 block, space for $ra
            dec->param_local = para_index++;
            dec->symTab = NULL;
            int err = localSymTab->insertRow(dec->symName, dec);
            // cout << "PARAM" << dec->symName << " " << dec->size << " " << dec->offset << " " << global_offset << endl;
            if(err == -1){
                print_error(-1, dec->symName);
            }
            else{   //if error in insertion then don't update global_offset variable
                global_offset = global_offset + dec->size;
            }
        }
    }
;

declarator: 
    IDENTIFIER 
    { 
        SymRow * dec = new SymRow();
        dec->symName = $1;
        dec->size = 1;
        dec->head = dec->tail = NULL;
        $$ = dec;
    } 
	| declarator '[' primary_expression ']' 
    {
        line_num = d_scanner.lineNr();
        //check whether the primay expression is an int constant and store its value in bnd
        int bnd;
        SymRow * dec;
        ExpAst * prim = $3;
        if(prim->only_int == false){
            print_error(-5, "");  						// array indices not integer
        }
        else{
            if(prim->int_value < 0){
                print_error(-6, ""); 					//array indices negative
            }
            else{
                bnd = prim->int_value;
                string s = std::to_string(bnd);
                dec = $1;
                var_type *tp = new var_type(s);
                if(dec->head == NULL){
                    dec->head = dec->tail = tp;
                }
                else{
                    (dec->tail)->type = tp;
                    dec->tail = tp;
                }
                dec->size = dec->size * bnd;        
            }

        }
        $$ = dec;
    }
    | '*' declarator     
    {
        SymRow * dec = $2;
        if(dec->head == NULL){
            var_type *tp = new var_type("*");
            dec->head = dec->tail = tp;
        }
        else{
            if(((dec->tail)->t)[0] == '*'){
                (dec->tail)->t = (dec->tail)->t + "*";
            }
            else{
                var_type *tp = new var_type("*");
                (dec->tail)->type = tp;
                dec->tail = tp;
            }
        }
        $$ = dec;
    }
;

compound_statement: 
    '{' '}'
    {
        StmtAst *s = new EMPTY();
        abstract_astnode *a = new BLOCK_STMT(s);
        $$ = a;
    }
	| '{' statement_list '}'
    {
        abstract_astnode *a = new BLOCK_STMT($2);
        $$ = a;
    } 
    | '{' declaration_list statement_list '}'
    {
        
        abstract_astnode *a = new BLOCK_STMT($3);
        $$ = a;
    } 
;

statement_list
	: statement	
    {
        StmtAst *a = new STMT_GROUP();
        a->pushSt($1);
        $$ = a;
    }	
    | statement_list statement
    {
        $1->pushSt($2);
        $$ = $1;
    }	
	;

statement: 
    '{' statement_list '}'  //a solution to the local decl problem
    {
        StmtAst *a = new BLOCK_STMT($2);
        $$ = a;
    }
    | selection_statement
    {
        $$ = $1;
    } 	
    | iteration_statement
    {
        $$ = $1;
    } 	
	| assignment_statement
    {
        $$ = $1;
    }	
    | RETURN expression ';'
    {
        line_num = d_scanner.lineNr();
        ExpAst * expr = $2;
        var_type * ret = ((globalSymTab->sym_rows.find(curr_fn))->second)->head;
        if(!type_match(ret, expr->type))
            print_error(-71, "");							//incompatible return types.
        casting_assign(ret, expr);
        StmtAst *a = new RETN(expr);
        $$ = a;
    }	
;

assignment_statement: 
    ';' 
    {
        StmtAst *a = new EMPTY();
        $$ = a;
    }
	|  expression ';'
    {
        ExpAst * expr = $1;
        StmtAst *a = new EXPR_STMT(expr);
        // expr->calculate_label(-1,1);
        // expr->print();
        // init_stack(max_stack_size);
        // expr->generate_code(1);
        $$ = a;
    }	
	;

expression: 
    logical_or_expression
    {
        $$ = $1;
    }
    | unary_expression '=' expression
    {
        line_num = d_scanner.lineNr();
        ExpAst* unary = $1;
        ExpAst* expr = $3;
        ExpAst * a = new EXP_ASSIGN(unary, expr);
        if(unary->ltype == false){
            print_error(-61, "");							//lvalue required as left operand of assignment
        }
        a->type = valid_assign(unary->type, expr);
        casting_assign(unary->type, expr);
        a->ltype = false;
        $$ = a;
    }
	;

logical_or_expression            // The usual hierarchy that starts here...
    : logical_and_expression
    {
        $$ = $1;
    }
    | logical_or_expression OR_OP logical_and_expression
    {
        line_num = d_scanner.lineNr();
        ExpAst *logic = $1;
        ExpAst *eq = $3;
        int c = casting_binary(logic, eq); // in case of an error this would give 0, > 0 only when both basic and all binary allow basic operands
        string bin_op = "OR_OP";
        switch(c){
            case 2: 
                bin_op = bin_op + "-FLOAT";
                break;
            case 1:
                bin_op = bin_op + "-INT";
                break;
        }
        ExpAst *a = new BIN_OP(bin_op, logic, eq);
        a->type = result_type(logic->type, eq->type, 0);
        a->ltype = false;
        a->only_int = logic->only_int && eq->only_int;
        a->int_value = logic->int_value || eq->int_value;        
        $$ = a;
    }
    ;

logical_and_expression:
    equality_expression
    {
        $$ = $1;
    }
    | logical_and_expression AND_OP equality_expression
    {
        line_num = d_scanner.lineNr();
        ExpAst *logic = $1;
        ExpAst *eq = $3;
        int c = casting_binary(logic, eq); // in case of an error this would give 0, > 0 only when both basic and all binary allow basic operands
        string bin_op = "AND_OP";
        switch(c){
            case 2: 
                bin_op = bin_op + "-FLOAT";
                break;
            case 1:
                bin_op = bin_op + "-INT";
                break;
        }

        ExpAst *a = new BIN_OP(bin_op, logic, eq);
        a->type = result_type(logic->type, eq->type, 0);
        a->ltype = false;
        a->only_int = logic->only_int && eq->only_int;
        a->int_value = logic->int_value && eq->int_value;        
        $$ = a;
    } 
;

equality_expression:
    relational_expression{
        $$ = $1;
    }
    | equality_expression EQ_OP relational_expression
    {
        line_num = d_scanner.lineNr();
        ExpAst * eq = $1;
        ExpAst * rel = $3;
        int c = casting_binary(eq, rel); // in case of an error this would give 0, > 0 only when both basic and all binary allow basic operands
        string bin_op = "EQ_OP";
        switch(c){
            case 2: 
                bin_op = bin_op + "-FLOAT";
                break;
            case 1:
                bin_op = bin_op + "-INT";
                break;
        }
        ExpAst *a = new BIN_OP(bin_op, eq, rel);
        a->type = result_type(eq->type, rel->type, 1);
        a->ltype = false;
        a->only_int = eq->only_int && rel->only_int;
        a->int_value = eq->int_value == rel->int_value;        
        $$ = a;
    }
	| equality_expression NE_OP relational_expression
	{
        line_num = d_scanner.lineNr();
        ExpAst * eq = $1;
        ExpAst * rel = $3;
        int c = casting_binary(eq, rel); // in case of an error this would give 0, > 0 only when both basic and all binary allow basic operands
        string bin_op = "NE_OP";
        switch(c){
            case 2: 
                bin_op = bin_op + "-FLOAT";
                break;
            case 1:
                bin_op = bin_op + "-INT";
                break;
        }
        ExpAst *a = new BIN_OP(bin_op, eq, rel);
        a->type = result_type(eq->type, rel->type, 1);
        a->ltype = false;
        a->only_int = eq->only_int && rel->only_int;
        a->int_value = eq->int_value != rel->int_value;        
        $$ = a;
    }
    ;

relational_expression:
    additive_expression
    {
        $$ = $1;
    }
    | relational_expression '<' additive_expression 
	{
        line_num = d_scanner.lineNr();
        ExpAst *rel = $1;
        ExpAst *add = $3;
        int c = casting_binary(rel, add); // in case of an error this would give 0, > 0 only when both basic and all binary allow basic operands
        string bin_op = "LT";
        switch(c){
            case 2: 
                bin_op = bin_op + "-FLOAT";
                break;
            case 1:
                bin_op = bin_op + "-INT";
                break;
        }
        ExpAst *a = new BIN_OP(bin_op, rel, add);
        a->type = result_type(rel->type, add->type, 2);
        a->ltype = false;
        a->only_int = rel->only_int && add->only_int;
        a->int_value = rel->int_value < add->int_value;        
        $$ = a;
    }
    | relational_expression '>' additive_expression 
    {
        line_num = d_scanner.lineNr();
        ExpAst *rel = $1;
        ExpAst *add = $3;
        int c = casting_binary(rel, add); // in case of an error this would give 0, > 0 only when both basic and all binary allow basic operands
        string bin_op = "GT";
        switch(c){
            case 2: 
                bin_op = bin_op + "-FLOAT";
                break;
            case 1:
                bin_op = bin_op + "-INT";
                break;
        }
        ExpAst *a = new BIN_OP(bin_op, rel, add);
        a->type = result_type(rel->type, add->type, 2);
        a->ltype = false;
        a->only_int = rel->only_int && add->only_int;
        a->int_value = rel->int_value > add->int_value;        
        $$ = a;
    }
    | relational_expression LE_OP additive_expression 
    {
        line_num = d_scanner.lineNr();
        ExpAst *rel = $1;
        ExpAst *add = $3;
        int c = casting_binary(rel, add); // in case of an error this would give 0, > 0 only when both basic and all binary allow basic operands
        string bin_op = "LE_OP";
        switch(c){
            case 2: 
                bin_op = bin_op + "-FLOAT";
                break;
            case 1:
                bin_op = bin_op + "-INT";
                break;
        }
        ExpAst *a = new BIN_OP(bin_op, rel, add);
        a->type = result_type(rel->type, add->type, 2);
        a->ltype = false;
        a->only_int = rel->only_int && add->only_int;
        a->int_value = rel->int_value <= add->int_value;        
        $$ = a;
    }
    | relational_expression GE_OP additive_expression 
	{
        line_num = d_scanner.lineNr();
        ExpAst *rel = $1;
        ExpAst *add = $3;
        int c = casting_binary(rel, add); // in case of an error this would give 0, > 0 only when both basic and all binary allow basic operands
        string bin_op = "GE_OP";
        switch(c){
            case 2: 
                bin_op = bin_op + "-FLOAT";
                break;
            case 1:
                bin_op = bin_op + "-INT";
                break;
        }
        ExpAst *a = new BIN_OP(bin_op, rel, add);
        a->type = result_type(rel->type, add->type, 2);
        a->ltype = false;
        a->only_int = rel->only_int && add->only_int;
        a->int_value = rel->int_value >= add->int_value;        
        $$ = a;
    }
    ;

additive_expression : 
    multiplicative_expression
    {
        $$ = $1;
    }
	| additive_expression '+' multiplicative_expression 
	{
        line_num = d_scanner.lineNr();
        ExpAst *add = $1;
        ExpAst *mult = $3;
        int c = casting_binary(add, mult); // in case of an error this would give 0, > 0 only when both basic and all binary allow basic operands
        string bin_op = "PLUS";
        switch(c){
            case 2: 
                bin_op = bin_op + "-FLOAT";
                break;
            case 1:
                bin_op = bin_op + "-INT";
                break;
        }
        ExpAst *a = new BIN_OP(bin_op, add, mult);
        a->type = result_type(add->type, mult->type, 3);
        a->ltype = false;
        a->only_int = mult->only_int && add->only_int;
        a->int_value = add->int_value + mult->int_value;        
        $$ = a;
    }
    | additive_expression '-' multiplicative_expression 
	{
        line_num = d_scanner.lineNr();
        ExpAst *add = $1;
        ExpAst *mult = $3;
        int c = casting_binary(add, mult); // in case of an error this would give 0, > 0 only when both basic and all binary allow basic operands
        string bin_op = "MINUS";
        switch(c){
            case 2: 
                bin_op = bin_op + "-FLOAT";
                break;
            case 1:
                bin_op = bin_op + "-INT";
                break;
        }
        ExpAst *a = new BIN_OP(bin_op, add, mult);
        a->type = result_type(add->type, mult->type, 4);
        a->ltype = false;
        a->only_int = mult->only_int && add->only_int;
        a->int_value = add->int_value - mult->int_value;        
        $$ = a;
    }
;

multiplicative_expression: 
    unary_expression
    {
        $$ = $1;
    }
	| multiplicative_expression '*' unary_expression 
	{
        line_num = d_scanner.lineNr();
        ExpAst *mult = $1;
        ExpAst *unary = $3;
        int c = casting_binary(mult, unary); // in case of an error this would give 0, > 0 only when both basic and all binary allow basic operands
        string bin_op = "MULT";
        switch(c){
            case 2: 
                bin_op = bin_op + "-FLOAT";
                break;
            case 1:
                bin_op = bin_op + "-INT";
                break;
        }
        ExpAst *a = new BIN_OP(bin_op, mult, unary);
        a->type = result_type(mult->type, unary->type, 5);
        a->ltype = false;
        a->only_int = mult->only_int && unary->only_int;
        a->int_value = mult->int_value * unary->int_value;        
        $$ = a;
    }
    | multiplicative_expression '/' unary_expression 
	{
        line_num = d_scanner.lineNr();
        ExpAst *mult = $1;
        ExpAst *unary = $3;
        int c = casting_binary(mult, unary); // in case of an error this would give 0, > 0 only when both basic and all binary allow basic operands
        string bin_op = "DIV";
        switch(c){
            case 2: 
                bin_op = bin_op + "-FLOAT";
                break;
            case 1:
                bin_op = bin_op + "-INT";
                break;
        }
        ExpAst *a = new BIN_OP(bin_op, mult, unary);
        a->type = result_type(mult->type, unary->type, 5);
        a->ltype = false;
        a->only_int = mult->only_int && unary->only_int;
        if(unary->int_value == 0)
            print_error(-81, ""); // division by 0
        a->int_value = mult->int_value / unary->int_value;
        $$ = a;
    }
;

unary_expression: 
    postfix_expression
    {
        $$ = $1;
    }
	| unary_operator postfix_expression 
	{
        line_num = d_scanner.lineNr();
        string unary = $1;
        ExpAst * post_exp = $2;
        ExpAst *a = new UN_OP(unary, post_exp);
        if(unary == "ref"){
            if(post_exp->ltype == false){					//check for ltype in case of ref.
                print_error(-64, "");
            }
            a->type = ref(post_exp->type);
            a->ltype = false;
            a->only_int = false;
            a->int_value = -1;
        }
        else if(unary == "deref"){
            a->type = deref(post_exp->type);
            a->ltype = true;        
            a->only_int = false;
            a->int_value = -1;
        }
        else if(unary == "not"){
            a->type = unary_not(post_exp->type);
            a->ltype = false;   							// definitely can not be ltype
            if(post_exp->only_int){
                a->only_int = true;
                a->int_value = (post_exp->int_value == 0);	// if != 0 return 0 else 1 
            }
            else{
                a->only_int = false;
                a->int_value = -1;
            }
        }
        else if(unary == "minus"){
            a->type = unary_minus(post_exp->type);
            a->ltype = false;   							// definitely can not be ltype
            if(post_exp->only_int){
                a->only_int = true;
                a->int_value = -post_exp->int_value; 		// if != 0 return 0 else 1 
            }
            else{
                a->only_int = false;
                a->int_value = -1;
            }
        }
        $$ = a;
    }
    ;

postfix_expression: 
    primary_expression
    {
        $$ = $1;
    }  				
    | IDENTIFIER '(' ')'
    {
        line_num = d_scanner.lineNr();
        string id = $1;
        ExpAst *e = new EXP_EMPTY();
        EXP_GROUP *eg = new EXP_GROUP();
        eg->pushEx(e);
        std::vector<ExpAst *> v;
        int not_print = function_parameter_match(id, v);  			// function existance checked in function_parameter_match
        ExpAst *a = new FUNC(id, eg);
        if(not_print == 1)
            a->type = ((globalSymTab->sym_rows.find(id))->second)->head;
        else
            a->type = new var_type("Void");
        a->ltype = false; 				// function calls can not appear as operand in the assignment operation
        a->only_int = false;
        a->int_value = -1;
        init_stack(max_stack_size);
        $$ = a;
    } 				
	| IDENTIFIER '(' expression_list ')' 
	{
        line_num = d_scanner.lineNr();
        string id = $1;
        EXP_GROUP * expr_list = $3;
        ExpAst *a = new FUNC(id, expr_list);
        vector<ExpAst *> Exp_List = expr_list->get_expression_list();
        int not_print = function_parameter_match(id, Exp_List);  // function existance checked in function_parameter_match
        if(not_print == 1)
            a->type = ((globalSymTab->sym_rows.find($1))->second)->head;
        else
            a->type = new var_type("Void");
        a->ltype = false; 			// function calls can not appear as operand in the assignment operation
        a->only_int = false;
        a->int_value = -1;
        init_stack(max_stack_size);
        $$ = a;
    }
    | postfix_expression '[' expression ']'
    {
        line_num = d_scanner.lineNr();
        ExpAst * post_exp = $1;
        ExpAst * expr = $3;
        ExpAst *a = new ARRAYREF(post_exp, expr);
        string exp_type = get_type(expr->type, "");
        a->type = deref(post_exp->type);
        if(exp_type != "int"){
            print_error(-5, "");  							// array indices not integer
        }   
        a->ltype = true;
        a->only_int = false;
        a->int_value = -1;
        $$ = a;
    } 
    | postfix_expression '.' IDENTIFIER
    {
        line_num = d_scanner.lineNr();
        ExpAst * post_exp = $1;
        ExpAst *a = new MEMBER(post_exp, d_scanner.matched());
        a->type = data_member_access(post_exp->type, $3, 0);
        a->ltype = true;
        a->only_int = false;
        a->int_value = -1;
        $$ = a;
    }
    | postfix_expression PTR_OP IDENTIFIER
    {
        line_num = d_scanner.lineNr();
        ExpAst * post_exp = $1;
        ExpAst *a = new ARROW(post_exp, d_scanner.matched());
        a->type = data_member_access(post_exp->type, $3, 1);
        a->ltype = true;
        a->only_int = false;
        a->int_value = -1;
        $$ = a;
    }
    | postfix_expression INC_OP
    {
        line_num = d_scanner.lineNr();
        ExpAst * post_exp = $1;
        ExpAst *a = new UN_OP("INC_OP", post_exp);
        
        if(post_exp->ltype == false){				//check for ltype compatibility
            print_error(-65, "");
        }

        if(is_struct(post_exp->type)){
            print_error(-26,"");
        }
        else
            a->type = post_exp->type;                             
        a->ltype = false;
        a->only_int = false;
        a->int_value = -1;
        $$ = a;
    }			
	;

primary_expression:
    IDENTIFIER
    {
        line_num = d_scanner.lineNr();
        ExpAst *a = new IDENTIFIER_REF($1);
        a->type = identifier_type($1);
        a->ltype = true;
        a->only_int = false;
        a->int_value = -1;
        $$ = a;
    }
    | INT_CONSTANT
    {
        line_num = d_scanner.lineNr();
        string i = d_scanner.matched();
        int value = 0;
        if(i[0] == '0' && (i[1] == 'x' || i[1] == 'X')){
            value = strtol(i.substr(2, i.length()).c_str(), NULL, 16);   
        }
        else if(i[0] == '0' && (i[1] == 'b' || i[1] == 'B')){
            value = strtol(i.substr(2, i.length()).c_str(), NULL, 2);   
        }
        else if(i[0] == '0'){
            value = strtol(i.substr(1, i.length()).c_str(), NULL, 8);   
        }
        else{
            value = stoi(i);
        }

        ExpAst * a = new INT_EXP(d_scanner.matched());
        a->type = new var_type("int");
        a->ltype = false;
        a->only_int = true;
        a->int_value = value;
        $$ = a; 
    } 
	| FLOAT_CONSTANT
    {
        line_num = d_scanner.lineNr();
        ExpAst * a = new FLOAT_EXP(d_scanner.matched());
        a->type = new var_type("float");
        a->ltype = false;
        a->only_int = false;
        a->int_value = -1;
        $$ = a;
    }
    | STRING_LITERAL
	{
        line_num = d_scanner.lineNr();
        ExpAst * a = new STRING_EXP(d_scanner.matched());
        a->type = new var_type("char*"); 				// considering strings as char*
        a->ltype = false;
        a->only_int = false;
        a->int_value = -1;
        $$ = a;
    }
    | '(' expression ')' 	
    {
        $$ = $2;
    }
;

expression_list: 
    expression
    {
        EXP_GROUP *a = new EXP_GROUP();
        a->pushEx($1);
        $$ = a;
    }
    | expression_list ',' expression
	{
        $1->pushEx($3);
        $$ = $1;
    }
    ;

unary_operator: 
    '-'	
    {
        string a = "minus";
        $$ = a;
    }
	| '!' 	
    {
        string a = "not";
        $$ = a;
    }
    | '&'
    {
        string a = "ref";
        $$ = a;
    }
    | '*'
    {
        string a = "deref";
        $$ = a;
    }
;

selection_statement: 
    IF '(' expression ')' statement ELSE statement
    {
        StmtAst *a = new IF_STMT($3, $5, $7);
        $$ = a;
    } 
	;

iteration_statement: 
    WHILE '(' expression ')' statement
    {
        StmtAst *a = new WHILE_STMT($3, $5);
        $$ = a;
    } 	
	| FOR '(' expression ';' expression ';' expression ')' statement
    {
        StmtAst *a = new FOR_STMT($3, $5, $7, $9);
        $$ = a;
    } 
;

declaration_list: 
    declaration
    {
    }  					
    | declaration_list declaration
    {
    }
;

declaration: 
    type_specifier declarator_list';' 
	{
        line_num = d_scanner.lineNr();
        std::pair<string,int> dec_type = $1;
        vector<SymRow *> dec = $2;
        for(int i = 0; i < dec.size(); i++){
            SymRow * row = dec[i];

            // updating the type
            if(row->head == NULL){
                var_type *tp = new var_type(dec_type.first);
                row->head = row->tail = tp;
            }
            else{
                if((row->tail)->t[0] == '*'){    		//pointer
                    (row->tail)->t = dec_type.first + (row->tail)->t;
                }
                else{
                    var_type *tp = new var_type(dec_type.first);
                    (row->tail)->type = tp;
                    row->tail = tp;
                }
            }

            int base_size = get_base_size(row->tail);
            row->size = base_size * row->size;

            if(get_type(row->tail, "") == "void"){
                print_error(-2, "");                    //variable declared as void
            }
            else{
                row->offset = global_offset;
                row->param_local = 0;
                row->symTab = NULL;
                int err = localSymTab->insertRow(row->symName, row);
                if(err == -1){
                    print_error(-1, row->symName);
                }
                else{   //if error in insertion then don't update global_offset variable
                    global_offset = global_offset - row->size;
                }
            }
        }
    }
;

declarator_list: 
    declarator
    {
        vector<SymRow *> dec;
        dec.push_back($1);
        $$ = dec;
    }
	| declarator_list ',' declarator 
 	{
        vector<SymRow *> dec = $1;
        dec.push_back($3);
        $$ = dec;
    }
;


