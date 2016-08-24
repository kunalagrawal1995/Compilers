#include <stdio.h>
void abstract_astnode::pushAST(abstract_astnode *st){

}

void StmtAst::pushSt(StmtAst *st){

}

void ExpAst::pushEx(ExpAst *ex){

}

void AST_GROUP::pushAST(abstract_astnode *ast1){
	ast_list.push_back(ast1);
}

void AST_GROUP::print(){
	for(int i=0; i<ast_list.size(); ++i){
		ast_list[i]->print();
		cout<<endl;
	}	
}

void AST_EMPTY::print(){
}

void EMPTY::print(){
	printf("(Empty)\n");
}

RETN::RETN(ExpAst * expr){
	exp = expr;
}

void RETN::print(){
	printf("(RETURN ");
	exp->print();
	printf(")\n");
}

IF_STMT::IF_STMT(ExpAst * expr, StmtAst *st1, StmtAst *st2){
	exp = expr;
	stmt1 = st1;
	stmt2 = st2;
}

void IF_STMT::print(){
	printf("(IF ");
	exp->print();
	stmt1->print();
	stmt2->print();
	printf(")\n");
}

WHILE_STMT::WHILE_STMT(ExpAst *expr, StmtAst *statement){
	exp = expr;
	stmt = statement;
}

void WHILE_STMT::print(){
	printf("(WHILE ");
	exp->print();
	stmt->print();
	printf(")\n");
}

FOR_STMT::FOR_STMT(ExpAst *expr1, ExpAst *expr2, ExpAst *expr3, StmtAst *statement){
	exp1 = expr1;
	exp2 = expr2;
	exp3 = expr3;
	stmt = statement;
}

void FOR_STMT::print(){
	printf("(FOR ");
	exp1->print();
	exp2->print();
	exp3->print();
	stmt->print();
	printf(")\n");
}

ASSIGN::ASSIGN(ExpAst *expr, ExpAst *expr2){
	exp1 = expr;
	exp2 = expr2;
}

void ASSIGN::print(){
	printf("(Ass ");
	exp1->print();
	exp2->print();
	printf(")\n");
}

BLOCK_STMT::BLOCK_STMT(StmtAst *statement){
	stmt = statement;
}

void BLOCK_STMT::print(){
	printf("(BLOCK [");
	stmt->print();
	printf("])\n");
}

void STMT_GROUP::pushSt(StmtAst *statement){
	statement_list.push_back(statement);
}

void STMT_GROUP::print(){
	for (int i = 0; i < statement_list.size(); ++i){
		// printf("\n");
		statement_list[i]->print();
	}
}

EXPR_STMT::EXPR_STMT(ExpAst * expr){
	exp = expr;
}

void EXPR_STMT::print(){
	exp->print();
}

BIN_OP::BIN_OP(string operation, ExpAst * op1, ExpAst * op2){
	to_cast = false;
	label = 0;
	op = operation;
	operand1 = op1;
	operand2 = op2;
}

void BIN_OP::print(){
	if(to_cast){
		printf("(TO-%s",cast.c_str());
	}
	printf("(%s LABEL: %d ", op.c_str(), label);
	operand1->print();
	operand2->print();
	printf(")");
	if(to_cast){
		printf(")");
	}
}

int BIN_OP::calculate_label(int parent, int is_left){
	// left and right are the left and the right labels respectively
	int left, right;
	
	left = operand1->calculate_label(-1, 1); 
	right = operand2->calculate_label(-1, 0);
	if(left == right){
		label = left + 1;
		return label;
	}
	else{
		label = min(max(left, right + 1), max(left+1, right));
		return label;
	}
	// framework for the more optimized version
	// int curr;
	// curr = getExpCode(op); // based on the operation, we decide the code for the current experation;
	// if(curr == parent && curr > 0){
	// 	sub_tree.insert(sub_tree)
	// }
	// else{
	// 	// allocate the ExpAst and return the vector with single ExpAst representing the entire subtree
	// 	// setting of label is any needs to occur here, when the final rearrangement occurs
	// }
}

// BIN_OP always needs 2 registers, mips convention CONFIRM THIS
void BIN_OP::generate_code(int n){
	if(only_int == true){
		int reg = register_stack.top();
		cout << "li " << "$" << reg << ", " << int_value << endl;
		return;
	}

	manage_expr(operand1, operand2, 1);
	if(operand1->only_int == false && operand2->only_int == false){
		int op_code = get_op_code(op);
		bin_operation(op_code);		
	}
	else if(operand1->only_int == false){
		int op_code = get_op_code(op);
		int reg = register_stack.top();
		switch(op_code){
			case 1: 
				output_command("addi", reg, reg, operand2->int_value, 1);
				break;
			case 2: 
				output_command("addi", reg, reg, operand2->int_value, 1);
				break;
			case 3: 
				output_command("multi", reg, reg, operand2->int_value, 1);
				break;
			case 4: 
				output_command("divi", reg, reg, operand2->int_value, 1);
				break;
		}
	}
	else if(operand2->only_int == false){
		int op_code = get_op_code(op);
		int reg = register_stack.top();
		
		switch(op_code){
			case 1: 
			{
				register_stack.pop();
				int reg2 = register_stack.top();
				operand1->generate_code(1);
				register_stack.push(reg);
				output_command("sub", reg, reg2, reg, 0);
				break;
			}
			case 2: 
				output_command("addi", reg, reg, operand1->int_value, 1);
				break;
			case 3: 
				output_command("multi", reg, reg, operand1->int_value, 1);
				break;
			case 4: 
				output_command("divi", reg, reg, operand1->int_value, 1);
				break;
		}
	}

}

UN_OP::UN_OP(string operation, ExpAst * op1){
	to_cast = false;
	op = operation;
	operand1 = op1;
}

void UN_OP::print(){
	if(to_cast){
		printf("(TO-%s",cast.c_str());
	}
	printf("(%s LABEL: %d ", op.c_str(), label);
	operand1->print();
	printf(")");
	if(to_cast){
		printf(")");
	}
}

int UN_OP::calculate_label(int parent, int is_left){
	int left = operand1->calculate_label(-1, 1);

	label = left; // currently I am taking that the same register can be used to store the result
	return label;
	// framework for more efficient code generation
	// vector<ExpAst*> left;
	// // unary, we are assuming no optimization
	// left = calculate_label(-1); // -1 because this is not commutable, just asking for the best in subchild
	// ExpAst * un = new UN_OP(op, left[1]);
	// vector<ExpAst*> sub_tree;
	// sub_tree.push_back(un);
	// un->label = left[1]->label; // neg can be done in same register, NEED TO CHECK on the other unary operators
	// if(un.label == 0)
	// 	un->label = un->label+1; // given the child was a leaf, we need a register to store the new value, hence the plus one

	// return sub_tree;
}

void UN_OP::generate_code(int n){
}

EXP_ASSIGN::EXP_ASSIGN(ExpAst *expr, ExpAst *expr2){
	to_cast = false;
	exp1 = expr;
	exp2 = expr2;
}

void EXP_ASSIGN::print(){
	if(to_cast){
		printf("(TO-%s",cast.c_str());
	}
	printf("(Ass ");
	exp1->print();
	exp2->print();
	printf(")\n");
	if(to_cast){
		printf(")");
	}
}

// TO BE IMPLEMENTED 
int EXP_ASSIGN::calculate_label(int parent, int is_left){
	int left_l = exp1->calculate_label(-1, 0);
	int right_l = exp2->calculate_label(-1, 1);
	if(left_l == right_l){
		label = left_l + 1;
		return label;
	}
	else{
		label = min(max(left_l, right_l + 1), max(left_l + 1, right_l));
		return label;
	}
}

void EXP_ASSIGN::generate_code(int n){
	manage_expr(exp1, exp2, 0); // do not deref the first exp
	int reg = register_stack.top();
	if(exp2->only_int == false){
		register_stack.pop();
		int reg2 = register_stack.top();
		register_stack.push(reg);
		cout << "sw " << "$" << reg2 << ", 0(" << reg << ")" << endl;
		cout << "lw " << "$" << reg << ", 0(" << reg << ")" << endl;
	}
	else{
		register_stack.pop();
		int reg2 = register_stack.top();
		exp2->generate_code(1);
		register_stack.push(reg);
		cout << "sw " << "$" << reg << ", 0(" << reg << ")" << endl;
		cout << "lw " << "$" << reg << ", 0(" << reg << ")" << endl;
	}
}

FLOAT_EXP::FLOAT_EXP(string p){
	to_cast = false;
	f = p;
}

void FLOAT_EXP::print(){
	if(to_cast){
		printf("(TO-%s",cast.c_str());
	}
	printf("(FloatConst %s)", f.c_str());
	if(to_cast){
		printf(")");
	}
}

// NEED TO CHANGE THIS 
int FLOAT_EXP::calculate_label(int parent, int is_left){
	label = 0;
	return label;
}

void FLOAT_EXP::generate_code(int n){
}

INT_EXP::INT_EXP(string p){
	to_cast = false;
	i = p;
}

void INT_EXP::print(){
	if(to_cast){
		printf("(TO-%s",cast.c_str());
	}
	printf("(IntConst %s)", i.c_str());
	if(to_cast){
		printf(")");
	}
}

int INT_EXP::calculate_label(int parent, int is_left){
	label = 0;
	return label;
}

void INT_EXP::generate_code(int n){
	int reg = register_stack.top();
	cout << "li " << "$" << reg << ", " << int_value << endl; 
}

STRING_EXP::STRING_EXP(string p){
	to_cast = false;
	s = p;
}

void STRING_EXP::print(){
	if(to_cast){
		printf("(TO-%s",cast.c_str());
	}
	printf("(StringConst %s)", s.c_str());
	if(to_cast){
		printf(")");
	}
}

int STRING_EXP::calculate_label(int parent, int is_left){
	int sub_tree;

	return sub_tree;
}

void STRING_EXP::generate_code(int n){
}

FUNC::FUNC(string name, ExpAst *expr){
	to_cast = false;
	fnname = name;
	exp = expr;
}

void FUNC::print(){
	if(to_cast){
		printf("(TO-%s",cast.c_str());
	}
	printf("(FuncCall (Id %s)", fnname.c_str());
	exp->print();
	printf(")");
	if(to_cast){
		printf(")");
	}
}

// TO BE IMPLEMENTED 
int FUNC::calculate_label(int parent, int is_left){
	int sub_tree;

	return sub_tree;
}

void FUNC::generate_code(int n){
}

void EXP_GROUP::pushEx(ExpAst *expr1){
	Exp_List.push_back(expr1);
}

void EXP_GROUP::print(){
	for (int i = 0; i < Exp_List.size(); ++i){
		Exp_List[i]->print();
	}
}

std::vector<ExpAst *> EXP_GROUP::get_expression_list(){
	return Exp_List;
}

int EXP_GROUP::calculate_label(int parent, int is_left){
	label = is_left;
	return label;
}

void EXP_GROUP::generate_code(int n){
}

void EXP_EMPTY::print(){
}

int EXP_EMPTY::calculate_label(int parent, int is_left){
	// label = is_left;
	return label;
}

void EXP_EMPTY::generate_code(int n){
}


IDENTIFIER_REF::IDENTIFIER_REF(string i){
	to_cast = false;
	s = i;
}

void IDENTIFIER_REF::print(){
	if(to_cast){
		printf("(TO-%s ",cast.c_str());
	}
	printf("(Id '%s' LABEL: %d )", s.c_str(), label);
	if(to_cast){
		printf(")");
	}
}

int IDENTIFIER_REF::calculate_label(int parent, int is_left){
	// label = is_left;
	label = 1; // in mips no adding from the register
	return label;
	// framework for the more optimized
	// vector<ExpAst*> sub_tree;
	// ExpAst* id = new IDENTIFIER_REF(s);
	// id->label = 0;
	// sub_tree.push_back(id);
	// return sub_tree;
}			

void IDENTIFIER_REF::generate_code(int n){
	// this needs to be loaded into register
	int reg = register_stack.top();
	if(n == 1)
		cout << "lw " << "$" << reg << ", " << (localSymTab->sym_rows.find(s))->second->offset << "($fp)"<< endl; // check on the fp thing
	if(n == 0)
		cout << "addi " << "$" <<  reg << ", $fp, " <<  (localSymTab->sym_rows.find(s))->second->offset << endl;
}

ARRAYREF::ARRAYREF(ExpAst *p, ExpAst * exp1){
	to_cast = false;
	s = p;
	exp = exp1;
}

void ARRAYREF::print(){
	if(to_cast){
		printf("(TO-%s",cast.c_str());
	}
	printf("(Array ");
	s->print();
	exp->print();
	printf(")");
	if(to_cast){
		printf(")");
	}
}

int ARRAYREF::calculate_label(int parent, int is_left){
	int left, right;
	
	left = s->calculate_label(-1, 1); 
	right = exp->calculate_label(-1, 0);
	if(left == right){
		label = left + 1;
		return label;
	}
	else{
		label = min(max(left, right + 1), max(left+1, right));
		return label;
	}
}

void ARRAYREF::generate_code(int n){
	if(exp->only_int == true){ // its an integer constant
		s->generate_code(0); // 0 is so that they dont evaluate the address just add to it
		int reg = register_stack.top();
		if((s->type)->type == NULL){
		// we have pointers, which we deref int *a; a[5] kinda thing
			cout << "lw " << "$" << reg << ", 0($" << reg << ")" << endl;
		}
		int offset = exp->int_value * get_size(type);
		output_command("addi", reg, reg, offset, 1);  
	}
	else{
		manage_expr(s, exp, 0);
		int reg = register_stack.top();
		if((s->type)->type == NULL){
		// we have pointers, which we deref int *a; a[5] kinda thing
			cout << "lw " << "$" << reg << ", 0($" << reg << ")" << endl;	
		}
		register_stack.pop();
		int reg2 = register_stack.top();
		register_stack.push(reg);
		output_command("multi", reg2, reg2, get_size(type), 1);
		output_command("add", reg, reg, reg2, 0);
	}

	int reg = register_stack.top();
	if(n == 1){
		cout << "lw " << "$" << reg << ", 0($" << reg << ")" << endl;	
	}
}

ARROW::ARROW(ExpAst * reference, string i){
	to_cast = false;
	ref = reference;
	s = i;
}

void ARROW::print(){
	if(to_cast){
		printf("(TO-%s",cast.c_str());
	}
	printf("(ARROW ");
	ref->print();
	printf("(Id '%s')", s.c_str());
	printf(")");
	if(to_cast){
		printf(")");
	}
}

// TO BE IMPLEMENTED 
int ARROW::calculate_label(int parent, int is_left){
	int sub_tree;

	return sub_tree;
}

void ARROW::generate_code(int n){
}

MEMBER::MEMBER(ExpAst * reference, string i){
	to_cast = false;
	ref = reference;
	s = i;
}

void MEMBER::print(){
	if(to_cast){
		printf("(TO-%s",cast.c_str());
	}
	printf("(MEMBER ");
	ref->print();
	printf("(Id '%s')", s.c_str());
	printf(")");
	if(to_cast){
		printf(")");
	}
}

// TO BE IMPLEMENTED 
int MEMBER::calculate_label(int parent, int is_left){
	int sub_tree;

	return sub_tree;
}

void MEMBER::generate_code(int n){
}



int get_size(var_type* t){
	if(t->type == NULL)
		return 4; // base case everything is 4
	else{
		return stoi(t->t) * get_size(t->type); // here assumption is that the head is an integer, which will be if the next is not NULL and this is not reference
	}
}

// n is the number of registers alloted, currently working on int
void init_stack(int n){
	for (int i = n+1; i >= 2; i--){
		register_stack.push(i); // filling the stack with the available register numbers
	}
}

void swap_register_stack(){
	// CHECK THE CASE WHERE THERE ARE LESS THAN 2 REGISTERS AVAILABLE
	int top = register_stack.top();
	register_stack.pop();
	int nxt = register_stack.top();
	register_stack.pop();
	register_stack.push(top);
	register_stack.push(nxt);
}

// SETHI-ULMANN algorithm
// given two expressions, the stack is global how to evaluate the expressions
// the top register contains the result for the left and the next contains the result for the right
void manage_expr(ExpAst *expr1, ExpAst *expr2, int arr){
	int left_l = expr1->label;
	int right_l = expr2->label;
	if(expr1->only_int == false && expr2->only_int == false){	
		if(left_l >= right_l && register_stack.size() > right_l){
			expr1->generate_code(arr);
			int reg = register_stack.top(); // this contains the result for the left expr
			register_stack.pop();
			expr2->generate_code(1);
			register_stack.push(reg);
		}
		else if(left_l < register_stack.size()){
			swap_register_stack();
			expr2->generate_code(1);
			int reg = register_stack.top();
			register_stack.pop();
			expr1->generate_code(arr);
			int reg2 = register_stack.top();
			register_stack.pop();
			register_stack.push(reg);
			register_stack.push(reg2);
		}
		else{ // now both the children need more than register_stack registers, use stack
			expr1->generate_code(arr);
			int reg = register_stack.top();
			cout << "PUSH " << reg << " ON STACK" << endl;
			// CONFIRM, expr2 can use the entire register stack available
			swap_register_stack(); 
			expr2->generate_code(1);
			reg = register_stack.top();
			register_stack.pop();
			int reg2 = register_stack.top();
			register_stack.pop();
			cout << "Push the value from stack back in the " << reg2 << endl;
			register_stack.push(reg);
			register_stack.push(reg2);
			// again rearrange the stack
		}
	}
	else{
		if(expr1->only_int == false){  
			expr1->generate_code(arr);
		}
		if(expr2->only_int == false){
			expr2->generate_code(1);
		}
	}
}

// convert the string to op_code
int get_op_code(string s){
	string s1 = s.substr(0,3);
	if(s1 == "MIN")
		return 1;
	if(s1 == "PLU")
		return 2;
	if(s1 == "MUL")
		return 3;
	return 4;
}

// apply the given operation
void bin_operation(int op_code){
	int reg = register_stack.top();
	register_stack.pop();
	int reg2 = register_stack.top();
	register_stack.push(reg);
	if(op_code == 1){
		output_command("sub", reg, reg, reg2, 0); 
	}
	if(op_code == 2){
		output_command("add", reg, reg, reg2, 0);
	}
	if(op_code == 3){
		cout << "mult " << "$" << reg << ", " << "$" << reg2 << endl;
		cout << "mflo " << "$" << reg << endl;
	}
	if(op_code == 4){
		// The inbuilt one checks if the value is zero before dividing, might implement that
		cout << "div " << "$" << reg << ", " << "$" << reg2 << endl;
		cout << "mflo " << "$" << reg << endl;
	}

}

// print the commands
void output_command(string s, int dest, int r1, int r2, int imm){
	if(imm == 0)
		cout << s << " " << "$" << dest << ", " << "$" << r1 << ", " << "$" << r2 << endl;
	else
		cout << s << " " << "$" << dest << ", " << "$" << r1 << ", " << r2 << endl;
}
