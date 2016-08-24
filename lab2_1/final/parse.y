%polymorphic INT: int ; FLOAT: float; TEXT: std::string; ABS: abstract_astnode*; STMT: StmtAst*; EXP: ExpAst*; REF: RefAst*;
%scanner Scanner.h
%scanner-token-function d_scanner.lex()
%type <ABS> translation_unit, struct_specifier, function_definition, compound_statement
%type <STMT> statement, statement_list, assignment_statement, selection_statement, iteration_statement
%type <EXP> expression, logical_and_expression, equality_expression, relational_expression, additive_expression, multiplicative_expression
%type <EXP> unary_expression, postfix_expression, primary_expression, expression_list
%type <REF> l_expression
%type <TEXT> unary_operator, IDENTIFIER
%token FLOAT INT VOID INT_CONSTANT FLOAT_CONSTANT
%token IF ELSE WHILE FOR RETURN
%token LE_OP GE_OP NE_OP EQ_OP AND_OP OR_OP INC_OP
%token OTHERS STRING_LITERAL STRUCT PTR_OP
%%

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
        abstract_astnode *b = new AST_GROUP();
        b->pushAST($1);
        $$ = b;

    } 
 	| translation_unit function_definition
    {
        $1->pushAST($2);
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
;

function_definition : 
    type_specifier fun_declarator compound_statement 
    {
        $$ = $3;
    }
;

type_specifier : 
    base_type
    | type_specifier '*'
;

base_type 
    : VOID 
    { 
    } 	
    | INT   
    { 
    } 
	| FLOAT 
    { 
    } 
    | STRUCT IDENTIFIER 
    { 
    } 
;

fun_declarator
	: IDENTIFIER '(' parameter_list ')' 
	| IDENTIFIER '(' ')' 
	;

parameter_list
	: parameter_declaration 
	| parameter_list ',' parameter_declaration 
	;

parameter_declaration
	: type_specifier declarator 
;

declarator
	: IDENTIFIER 
    { 
    } 
	| declarator '[' constant_expression ']' 
    {
    }
;

constant_expression : 
    INT_CONSTANT 
    | FLOAT_CONSTANT 
;

compound_statement: 
    '{' '}'
    {
        StmtAst *s = new EMPTY();
        abstract_astnode *a = new BLOCK_STMT(s);
        $$ = a;
        $$->print();
    }
	| '{' statement_list '}'
    {
        abstract_astnode *a = new BLOCK_STMT($2);
        $$ = a;
        $$->print();
    } 
    | '{' declaration_list statement_list '}'
    {
        abstract_astnode *a = new BLOCK_STMT($3);
        $$ = a;
        $$->print();
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
        StmtAst *a = new RETN($2);
        $$ = a;
    }	
;

assignment_statement: 
    ';' 
    {
        StmtAst *a = new EMPTY();
        $$ = a;
    }
	|  l_expression '=' expression ';'
    {
        StmtAst *a = new ASSIGN($1, $3);
        $$ = a;
    }	
	;

expression: 
    logical_and_expression
    {
    	$$ = $1;
    }
    | expression OR_OP logical_and_expression
	{
		ExpAst *a = new BIN_OP("OR_OP", $1, $3);
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
        ExpAst *a = new BIN_OP("AND_OP", $1, $3);
        $$ = a;
    } 
	;

equality_expression:
    relational_expression{
        $$ = $1;
    } 
    | equality_expression EQ_OP relational_expression
    {
        ExpAst *a = new BIN_OP("EQ_OP", $1, $3);
        $$ = a;
    } 	
	| equality_expression NE_OP relational_expression
	{
        ExpAst *a = new BIN_OP("NE_OP", $1, $3);
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
        ExpAst *a = new BIN_OP("LT", $1, $3);
        $$ = a;
    }
    | relational_expression '>' additive_expression 
    {
        ExpAst *a = new BIN_OP("GT", $1, $3);
        $$ = a;
    }
    | relational_expression LE_OP additive_expression 
    {
        ExpAst *a = new BIN_OP("LE_OP", $1, $3);
        $$ = a;
    }
    | relational_expression GE_OP additive_expression 
	{
        ExpAst *a = new BIN_OP("GE_OP", $1, $3);
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
        ExpAst *a = new BIN_OP("PLUS", $1, $3);
        $$ = a;
    }
    | additive_expression '-' multiplicative_expression 
	{
        ExpAst *a = new BIN_OP("MINUS", $1, $3);
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
        ExpAst *a = new BIN_OP("MULT", $1, $3);
        $$ = a;
    }
    | multiplicative_expression '/' unary_expression 
	{
        ExpAst *a = new BIN_OP("DIV", $1, $3);
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
        ExpAst *a = new UN_OP($1, $2);
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
        ExpAst *e = new EXP_EMPTY();
        ExpAst *a = new FUNC($1, e);
        $$ = a;
    } 				
	| IDENTIFIER '(' expression_list ')' 
	{
        ExpAst *a = new FUNC($1, $3);
        $$ = a;
    }
    | l_expression INC_OP
    {
        ExpAst *a = new UN_OP("INC_OP", $1);
        $$ = a;
    } 				
	;

primary_expression: 
    l_expression
    {
        $$ = $1;
    }
    | l_expression '=' expression
    {
        ExpAst *a = new EXP_ASSIGN($1, $3);
        $$ = a; 
    }   
    | '&' l_expression
    {
        ExpAst *a = new POINTER($2);
        $$ = a;
    }
    | INT_CONSTANT
    {
        ExpAst * a = new INT_EXP(d_scanner.matched());
        $$ = a; 
    } 
	| FLOAT_CONSTANT
    {
        ExpAst * a = new FLOAT_EXP(d_scanner.matched());
        $$ = a;
    }
    | STRING_LITERAL
	{
        ExpAst * a = new STRING_EXP(d_scanner.matched());
        $$ = a;
    }
    | '(' expression ')' 	
    {
        $$ = $2;
    }
;

l_expression: 
    IDENTIFIER
    {
        RefAst *a = new IDENTIFIER_REF($1);
        $$ = a;
    }
    | l_expression '[' expression ']'
    {
        RefAst *a = new ARRAYREF($1, $3);
        $$ = a;
    } 	
    | '*' l_expression
    {
        RefAst *a = new DEREF($2);
        $$ = a;
    }      
    | l_expression '.' IDENTIFIER
    {
        RefAst *a = new MEMBER($1, d_scanner.matched());
        $$ = a;
    }   
    | l_expression PTR_OP IDENTIFIER	
    {
        RefAst *a = new ARROW($1, d_scanner.matched());
        $$ = a;
    }   
;

expression_list: 
    expression
    {
        ExpAst *a = new EXP_GROUP();
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
    }  //modified this production
;

declaration_list
    : declaration  					
    | declaration_list declaration
;

declaration
	: type_specifier declarator_list';' 
	;

declarator_list
	: declarator
	| declarator_list ',' declarator 
 	;


