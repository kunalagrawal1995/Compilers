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

void AST_GROUP::generate_code(int n){
	cout << "AST_GROUP" << endl;
	for(int i = 0; i < ast_list.size(); i++){
		ast_list[i]->generate_code(n);
	}
}

void AST_GROUP::print(){
	for(int i=0; i<ast_list.size(); ++i){
		ast_list[i]->print();
		cout<<endl;
	}	
}

void AST_EMPTY::generate_code(int n){

}

void AST_EMPTY::print(){
}

void EMPTY::generate_code(int n){

}

void EMPTY::print(){
	printf("(Empty)\n");
}

RETN::RETN(ExpAst * expr){
	exp = expr;
}

void RETN::generate_code(int n){

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
void IF_STMT::generate_code(int n){
	exp->calculate_label(-1, -1);
	init_stack(max_stack_size);
	init_float_stack(max_stack_size);
	exp->generate_code(1);

	var_type *vt = exp->type;
	string st = get_type(vt, "");
	int reg = register_stack.top();
	int freg = float_register_stack.top();
	float_register_stack.pop();
	int freg2 = float_register_stack.top();
	float_register_stack.push(freg);
	string code_s;
	if(st == "float"){
		code_s = "mtc1 $0, $f" + to_string(freg2);
		cout << code_s << endl;
		code_s = "c.eq.s $f" + to_string(freg) + ", $f" + to_string(freg2);
		cout << code_s << endl;
		code_s = "bc1t $L" + to_string(label_count);
		cout << code_s << endl;
		int lc = label_count;
		label_count++;

		stmt1->generate_code(1);
		code_s = "b $L" + to_string(label_count);
		cout << code_s << endl; 

		code_s = "$L" + to_string(lc) + ":" ;
		cout << code_s << endl;
		lc = label_count;
		label_count++;
		stmt2->generate_code(1);
		code_s = "$L" + to_string(lc) + ":" ;
		cout << code_s << endl;

	}
	else{
		code_s = "beq $0, $" + to_string(reg) + ", $L" + to_string(label_count);
		cout << code_s << endl;
		int lc = label_count;
		label_count++;

		stmt1->generate_code(1);
		code_s = "b $L" + to_string(label_count);
		cout << code_s << endl; 

		code_s = "$L" + to_string(lc) + ":" ;
		cout << code_s << endl;
		lc = label_count;
		label_count++;
		stmt2->generate_code(1);
		code_s = "$L" + to_string(lc) + ":" ;		
		cout << code_s << endl;
	}
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

void WHILE_STMT::generate_code(int n){

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

void FOR_STMT::generate_code(int n){

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

void ASSIGN::generate_code(int n){

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

void BLOCK_STMT::generate_code(int n){
	stmt->generate_code(n);
}

void BLOCK_STMT::print(){
	printf("(BLOCK [");
	stmt->print();
	printf("])\n");
}

void STMT_GROUP::pushSt(StmtAst *statement){
	statement_list.push_back(statement);
}

void STMT_GROUP::generate_code(int n){
	for (int i = 0; i < statement_list.size(); ++i){
		statement_list[i]->generate_code(n);
	}
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

void EXPR_STMT::generate_code(int n){
	// calculate label for the expression -> initialize a new register stack -> generate code for the expression
	exp->calculate_label(-1, 1);
	init_stack(max_stack_size);
	init_float_stack(max_stack_size);
	exp->generate_code(n);
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
	// curr = getExpCode(op); // based on the operation, we decide the code for the current expression;
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

	int op_code = get_op_code(op);
	int reg = register_stack.top();
	int freg = float_register_stack.top();
	string expr_type = get_type(this->type, "");
	string operand_type = op.substr(op.length()-5, 5);
	// either expression evaluates to float or the operands are float	
	if(expr_type != "float" && operand_type != "FLOAT"){ // anything other than float works like normal integers
		if(operand1->only_int == false && operand2->only_int == false){
			manage_expr(operand1, operand2, 1);
			bin_operation(op_code);		
		}
		else if(operand1->only_int == false){
			switch(op_code){
				case 1: 
					operand1->generate_code(1);
					output_command("addi", reg, reg, operand2->int_value, 1);
					break;
				case 2: 
					operand1->generate_code(1);
					output_command("addi", reg, reg, operand2->int_value, 1);
					break;
				case 3: 
					operand1->generate_code(1);
					output_command("muli", reg, reg, operand2->int_value, 1);
					break;
				case 4: 
					operand1->generate_code(1);
					output_command("divi", reg, reg, operand2->int_value, 1);
					break;
				case 5:
				{
					if(operand2->int_value == 0){
						cout << "li " << "$" << reg << ", " << 0;
					}
					else{
						operand1->generate_code(1);
						output_command("sltu", reg, 0, reg, 0);
					}
					break;
				}
				case 6:
				{
					if(operand2->int_value != 0){
						cout << "li " << "$" << reg << ", " << 1;
					}
					else{
						operand1->generate_code(1);
						output_command("sltu", reg, 0, reg, 0);
					}
					break;	
				}
				case 7:
				{
					operand1->generate_code(1);
					int val = operand2->int_value;
					output_command("slt", reg, reg, val, 1);
					break;
				}
				case 8:
				{
					operand1->generate_code(1);
					int val = operand2->int_value;
					output_command("slt", reg, reg, val+1, 1);
					break;
				}
				case 9:
				{
					operand1->generate_code(1);
					int val = operand2->int_value;
					output_command("slt", reg, reg, val+1, 1);
					output_command("xori", reg, reg, 1, 1);
					break;
				}
				case 10:
				{
					operand1->generate_code(1);
					int val = operand2->int_value;
					output_command("slt", reg, reg, val, 1);
					output_command("xori", reg, reg, 1, 1);
					break;
				}
				case 11:
				{
					operand1->generate_code(1);
					int val = operand2->int_value;
					if(val != 0){
						output_command("xori", reg, reg, val, 1);
					}
					output_command("sltu", reg, reg, 1, 1);
					break;
				}
				case 12:
				{
					operand1->generate_code(1);
					int val = operand2->int_value;
					if(val != 0){
						output_command("xori", reg, reg, val, 1);
					}
					output_command("sltu", reg, 0, reg, 0);
					break;
				}
			}
		}
		else if(operand2->only_int == false){
			switch(op_code){
				case 1: 
				{
					operand2->generate_code(1);
					register_stack.pop();
					int reg2 = register_stack.top();
					operand1->generate_code(1);
					register_stack.push(reg);
					output_command("sub", reg, reg2, reg, 0);
					break;
				}
				case 2: 
					operand2->generate_code(1);
					output_command("addi", reg, reg, operand1->int_value, 1);
					break;
				case 3: 
					operand2->generate_code(1);
					output_command("multi", reg, reg, operand1->int_value, 1);
					break;
				case 4:{ 
					operand2->generate_code(1);
					register_stack.pop();
					int reg2 = register_stack.top();
					operand1->generate_code(1);
					register_stack.push(reg);
					output_command("div", reg, reg2, reg, 0);
					break;
				}
				case 5:
				{
					if(operand1->int_value == 0){
						cout << "li " << "$" << reg << ", " << 0;
					}
					else{
						operand2->generate_code(1);
						output_command("sltu", reg, 0, reg, 0);
					}
					break;
				}
				case 6:
				{
					if(operand2->int_value != 0){
						cout << "li " << "$" << reg << ", " << 1;
					}
					else{
						operand2->generate_code(1);
						output_command("sltu", reg, 0, reg, 0);
					}
					break;	
				}
				case 7:
				{
					operand2->generate_code(1);
					int val = operand1->int_value;
					output_command("slt", reg, reg, val+1, 1);
					output_command("xori", reg, reg, 1, 1);
					break;
				}
				case 8:
				{
					operand2->generate_code(1);
					int val = operand1->int_value;
					output_command("slt", reg, reg, val, 1);
					output_command("xori", reg, reg, 1, 1);
					break;
				}
				case 9:
				{
					operand2->generate_code(1);
					int val = operand1->int_value;
					output_command("slt", reg, reg, val, 1);
					break;
				}
				case 10:
				{
					operand2->generate_code(1);
					int val = operand1->int_value;
					output_command("slt", reg, reg, val+1, 1);
					break;
				}
				case 11:
				{
					operand2->generate_code(1);
					int val = operand1->int_value;
					if(val != 0){
						output_command("xori", reg, reg, val, 1);
					}
					output_command("sltu", reg, reg, 1, 1);
				}
				case 12:
				{
					operand2->generate_code(1);
					int val = operand1->int_value;
					if(val != 0){
						output_command("xori", reg, reg, val, 1);
					}
					output_command("sltu", reg, 0, reg, 0);
					break;
				}
			}
		}
	}
	else{ 
	// the operator is float
	// based on the implementation both the expressions would be in the float registers on the top of the float stack
	// the stack management is not there yet, need to implement it
		// cout << "FLOAT OPERATION" << endl;
		if(op_code != 5 && op_code != 6){
			operand1->generate_code(1); // output in freg
			float_register_stack.pop();
			int freg2 = float_register_stack.top();
			operand2->generate_code(1); // output in freg2
			float_register_stack.push(freg);
			float_bin_operation(op_code);
		}
		else{
			operand1->generate_code(1);
			float_register_stack.pop();
			int freg2 = float_register_stack.top();
			cout << "mtc1 $0, $f" << freg2 << endl; 
			if(op_code == 5){
				cout << "c.eq.s " << "$f" << freg << ", $f" << freg2 << endl;
				cout << "bc1t $L" << label_count << endl;
				int lc = label_count;
				operand2->generate_code(1);
				cout << "mtc1 $0, $f" << freg << endl;  
				cout << "c.eq.s " << "$f" << freg << ", $f" << freg2 << endl;
				cout << "bc1t $L" << lc << endl;
				cout << "li " << "$" << reg << ", 1" << endl;
				cout << "b " << "$L" << label_count+1 << endl;
				cout << "$L" << lc << ":" << endl;
				cout << "move " << "$" << reg << ", $0" << endl;
				cout << "$L" << label_count+1 << ":" << endl;
				label_count+=2;
			}
			else{
				cout << "c.eq.s " << "$f" << freg << ", $f" << freg2 << endl;
				cout << "bc1f $L" << label_count << endl;
				int lc = label_count;
				operand2->generate_code(1);
				cout << "mtc1 $0, $f" << freg << endl;  
				cout << "c.eq.s " << "$f" << freg << ", $f" << freg2 << endl;
				cout << "bc1f $L" << lc << endl;
				cout << "move " << "$" << reg << ", $0" << endl;
				cout << "b " << "$L" << label_count+1 << endl;
				cout << "$L" << lc << ":" << endl;
				cout << "li " << "$" << reg << ", 1" << endl;
				cout << "$L" << label_count+1 << ":" << endl;
				label_count+=2;
			}
			float_register_stack.push(freg);
		}
	}

	if(to_cast){
		if(cast == "FLOAT"){ // int to float
			cout << "mtc1 " << "$" << reg << ", $f" << freg << endl;
			cout << "cvt.s.w " << "$f" << freg << ", $f" << freg << endl;
		}
		else if(cast == "INT"){ // int to float
			cout << "cvt.w.s " << "$f" << freg << ", $f" << freg << endl;
			cout << "mfc1 " << "$" << reg << ", $f" << freg << endl;
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
	label = operand1->calculate_label(-1, 1);
	return label;
}

void UN_OP::generate_code(int n){
	if(only_int == true){
		int reg = register_stack.top();
		cout << "li " << "$" << reg << ", " << int_value << endl;
		return;
	}
	string expr_type = get_type(operand1->type, "");
	if(expr_type == "float"){
		if(op == "minus"){
			operand1->generate_code(1);
			int freg = float_register_stack.top();
			float_register_stack.pop();
			int freg2 = float_register_stack.top();
			float_register_stack.push(freg);
			string code = std::string("mtc1 ") + std::string("$0") + std::string(", ") + std::string("$f") + to_string(freg2);
			cout << code << endl;
			code = std::string("sub.s ") + std::string("$f") + to_string(freg) + std::string(", ") + std::string("$f") + to_string(freg2) + std::string(", ") + std::string("$f") + to_string(freg);
			cout << code << endl;
		}
		else if (op == "not"){
			operand1->generate_code(1);
			int freg = float_register_stack.top();
			float_register_stack.pop();
			int freg2 = float_register_stack.top();
			int reg = register_stack.top();
			string code;
			code = std::string("li ") + "$" + to_string(reg) + ", " + to_string(1);
			cout << code << endl;
			code = std::string("mtc1 ") + "$0" + ", " + "$f" + to_string(freg2);
			cout << code << endl;
			code = std::string("c.eq.s ") + "$f" + to_string(freg) + ", " + "$f" + to_string(freg2);
			cout << code << endl;
			code = std::string("bc1t ") + "$L" + to_string(label_count);
			cout << code << endl;
			code = std::string("li ") + "$" + to_string(reg) + ", " + "0";
			cout << code << endl;
			code = std::string("$L") + to_string(label_count) + ":";
			cout << code << endl;
			code = std::string("mtc1 ") + "$" + to_string(reg) + ", " + "$f" + to_string(freg);
			cout << code << endl;
			code = std::string("cvt.s.w ") + "$f" + to_string(freg) + ", " + "$f" + to_string(freg);
			cout << code << endl;
			label_count++;
		}
		else if(op == "ref"){
			operand1->generate_code(0);
		}
		else if(op == "deref"){
			//operand of deref is always an integer
			cout << " # PAIN : you understood wrong. operand of deref is a float." << endl;
		}
		else if(op == "INC_OP"){
			operand1->generate_code(1);
			int freg = float_register_stack.top();
			float_register_stack.pop();
			int freg2 = float_register_stack.top();
			float_register_stack.push(freg);
			int reg = register_stack.top();
			string code;
			code = std::string("li.s ") + "$f" + to_string(freg2) + ", 1.0";
			cout << code << endl;
			code = std::string("add.s ") + "$f" + to_string(freg) + ", "  + "$f" + to_string(freg) + ", "  + "$f" + to_string(freg2);
			cout << code << endl;
			operand1->generate_code(0);
			code = std::string("swc1 ") + "$f" + to_string(freg) + ", " + "0($" + to_string(reg) + ")";
			cout << code << endl;
			code = std::string("li.s ") + "$f" + to_string(freg2) + ", -1.0";
			cout << code << endl;
			code = std::string("add.s ") + "$f" + to_string(freg) + ", " + "$f" + to_string(freg) + ", " + "$f" + to_string(freg2);
			cout << code << endl;
		}
	}
	else{		// everything except float
		// manage_unary_expr(operand1, 1);
		if(op == "minus"){
			operand1->generate_code(1);
			int reg = register_stack.top();
			cout << "subu " << "$" << reg << ", " << "$0" << ", " << "$" << reg <<endl;
		}
		else if (op == "not"){
			operand1->generate_code(1);
			int reg = register_stack.top();
			cout << "sltu " << "$" << reg << ", " << "$" << reg << ", " << "1" <<endl;
		}
		else if (op == "ref"){
			operand1->generate_code(0);
			//ref is allowed only if ltype == true. for only identifiers(done), array(done), member(left), arrow(left).
		}
		else if (op == "deref"){
			operand1->generate_code(1);
			int reg = register_stack.top();
			if(expr_type == "float*"){
				//output is stored in a float stack.
				int freg = float_register_stack.top();
				string code = std::string("lwc1 ") + "$f" + to_string(freg) +  ", " + "0($" + to_string(reg) + ")";
				cout << code << endl;
			}
			else{
			cout << "lw " << "$" << reg << ", " << "0" << "(" << "$" << reg << ")" <<endl;
			}
		}
		// inc_op is implemented such that it a++ returns a, and will increase the value in stack by 1
		else if(op == "INC_OP"){
			operand1->generate_code(1);
			int reg = register_stack.top();	//has identifier val
			register_stack.pop();
			int reg2 = register_stack.top();
			string code = std::string("addiu ") + "$" + to_string(reg) + ", " + "$" + to_string(reg) + ", " + "1";
			cout << code << endl;
			operand1->generate_code(0);	//reg2 will store addr of operand1
			register_stack.push(reg);	//restore stack config
			code =  std::string("sw ") + "$" + to_string(reg) + ", " + "0($" + to_string(reg2) + ")";
			cout << code << endl;
			code = std::string("addiu ")  + "$" + to_string(reg) + ", " +  "$" + to_string(reg) + ", "  + "-1";
			cout << code << endl;
		}
	}
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
	string type = get_type(this->type, "");
	if(type == "float"){
		int freg = float_register_stack.top();
		exp2->generate_code(1);
		float_register_stack.pop();

		int reg = register_stack.top();
		exp1->generate_code(0);
		float_register_stack.push(freg);
		cout << "swc1 " << "$f" << freg << ", 0($" << reg << ")" << endl; 
		cout << "lwc1 " << "$f" << freg << ", 0($" << reg << ")" << endl; 
	}
	else{
		manage_expr(exp1, exp2, 0); // do not deref the first exp
		int reg = register_stack.top();
		if(exp2->only_int == false){
			register_stack.pop();
			int reg2 = register_stack.top();
			register_stack.push(reg);
			cout << "sw " << "$" << reg2 << ", 0($" << reg << ")" << endl;
			cout << "lw " << "$" << reg << ", 0($" << reg << ")" << endl;
		}
		else{
			register_stack.pop();
			int reg2 = register_stack.top();
			exp2->generate_code(1);
			register_stack.push(reg);
			cout << "sw " << "$" << reg2 << ", 0($" << reg << ")" << endl;
			cout << "lw " << "$" << reg << ", 0($" << reg << ")" << endl;
		}
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
	label = 1;
	return label;
}

void FLOAT_EXP::generate_code(int n){
	int freg = float_register_stack.top();
	int reg = register_stack.top();
	if(to_cast == false)
		cout << "li.s " << "$f" << freg << ", " << f << endl; // loading into single float register the const value 
	else{
		int int_value = (int)stof(f);
		cout << "li " << "$" << reg << ", " << int_value << endl; 
	}
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
	int freg = float_register_stack.top();
	if(to_cast == false)
		cout << "li " << "$" << reg << ", " << int_value << endl; 
	else{
		cout << "li.s " << "$f" << freg << ", " << int_value << ".0" << endl;
	}
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
	string s1;
	s1 = ".data";
	cout << s1 << endl;
	s1 = "$string" + to_string(string_count) + ": .asciiz " + s;
	cout << s1 << endl;
	s1 = ".text";
	string_count++;
	cout << s1 << endl;
}

FUNC::FUNC(string name, EXP_GROUP *expr){
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
	if(fnname == "printf"){
		vector<ExpAst *> param = exp->get_expression_list();
		for (int i = 0; i < param.size(); ++i){
			var_type *vt = param[i]->type;
			string st = get_type(vt, "");
			int reg = register_stack.top();
			int freg = float_register_stack.top();
			param[i]->generate_code(1);
			if(st == "char*"){
				string s = "li $v0, 4";
				cout << s << endl;
				s = "la $a0, $string" + to_string(string_count-1);
				cout << s << endl;	 
				s = "syscall";
				cout << s << endl;
			}
			else if(st == "int"){
				string s = "li $v0, 1";
				cout << s << endl;
				s = "move $a0, $" + to_string(reg);
				cout << s << endl;	 
				s = "syscall";
				cout << s << endl;
			}
			else if(st == "float"){
				string s = "li $v0, 2";
				cout << s << endl;
				s = "mov.s $f12, $f" + to_string(freg);
				cout << s << endl;	 
				s = "syscall";
				cout << s << endl;
			}
		}
	}
	else{
	// set-up parameters
	// TO BE IMPLEMENTED	
	// iterate over exp, evaluate each exp expressions, push on stack as parameter
	// jal instr

		cout << "jal " << fnname << endl;
	}
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
	int freg = float_register_stack.top();
	string type = get_type(this->type, "");
	//load address, casting does not work here
	if(n == 0) // in n we are just loading the address to idenntifier, no matter float or int the code remains the same
		cout << "addi " << "$" <<  reg << ", $fp, " <<  (localSymTab->sym_rows.find(s))->second->offset << endl;
	
	//load value
	if(n == 1 && type != "float"){
		cout << "lw " << "$" << reg << ", " << (localSymTab->sym_rows.find(s))->second->offset << "($fp)"<< endl; // check on the fp thing
	}
	else if(n == 1){
		cout << "lwc1 " << "$f" << freg << ", " << (localSymTab->sym_rows.find(s))->second->offset << "($fp)"<< endl; // check on the fp thing
	}

	// handelling casting in case we are loading a register 
	if(n == 1 and to_cast){
		if(cast == "FLOAT"){ // int to float
			cout << "mtc1 " << "$" << reg << ", $f" << freg << endl;
			cout << "cvt.s.w " << "$f" << freg << ", $f" << freg << endl;
		}
		else if(cast == "INT"){ // int to float
			cout << "cvt.w.s " << "$f" << freg << ", $f" << freg << endl;
			cout << "mfc1 " << "$" << reg << ", $f" << freg << endl;
		}
	}
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
	string exp_type = get_type(this->type, "");
	if(exp->only_int == true){ // its an integer constant
		s->generate_code(0); // 0 is so that they dont evaluate the address just add to it
		int reg = register_stack.top();
		if((s->type)->type == NULL){
		// we have pointers, which we deref int *a; a[5] kinda thing
			cout << "lw " << "$" << reg << ", 0($" << reg << ")" << endl;
		}
		int offset = exp->int_value * get_size(type);
		output_command("addi", reg, reg, -offset, 1);  
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
		output_command("muli", reg2, reg2, get_size(type), 1);
		output_command("sub", reg, reg, reg2, 0);
	}

	int reg = register_stack.top();
	int freg = float_register_stack.top();
	if(n == 1 && exp_type != "float"){
		cout << "lw " << "$" << reg << ", 0($" << reg << ")" << endl;	
	}
	else if(n == 1 && exp_type == "float"){
		cout << "lwc1 " << "$f" << freg << ", 0($" << reg << ")" << endl;	
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
	// making the stack empty if its not already
	while(!register_stack.empty()){
		register_stack.pop();
	}


	for (int i = n+1; i >= 4; i--){
		register_stack.push(i); // filling the stack with the available register numbers
	}
	register_stack.push(2);
	register_stack.push(3);
}

void init_float_stack(int n){
	// making the stack empty if its not already
	while(!float_register_stack.empty()){
		float_register_stack.pop();
	}

	for (int i = n-1; i >= 0; i--){
		float_register_stack.push(i); // filling the stack with the available register numbers
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
	string s1 = s.substr(0,2);
	if(s1 == "MI")
		return 1;
	if(s1 == "PL")
		return 2;
	if(s1 == "MU")
		return 3;
	if(s1 == "DI")
		return 4;
	if(s1 == "AN")
		return 5;
	if(s1 == "OR")
		return 6;
	if(s1 == "LT")
		return 7;
	if(s1 == "LE")
		return 8;
	if(s1 == "GT")
		return 9;
	if(s1 == "GE")
		return 10;
	if(s1 == "EQ")
		return 11;
	if(s1 == "NE")
		return 12;
}

// apply the given operation
void bin_operation(int op_code){
	int reg = register_stack.top();
	register_stack.pop();
	int reg2 = register_stack.top();
	register_stack.push(reg);
	switch(op_code){
		case 1:
		{
			output_command("sub", reg, reg, reg2, 0); 
			break;
		}
		case 2:
		{
			output_command("add", reg, reg, reg2, 0);
			break;
		}
		case 3:
		{
			cout << "mult " << "$" << reg << ", " << "$" << reg2 << endl;
			cout << "mflo " << "$" << reg << endl;
			break;	
		}
		case 4:
		{
			// The inbuilt one checks if the value is zero before dividing, might implement that
			cout << "div " << "$" << reg << ", " << "$" << reg2 << endl;
			cout << "mflo " << "$" << reg << endl;
			break;
		}
		case 5:
		{
			cout << "beq " << "$" << reg << ", $0, $L" << label_count << endl;
			cout << "beq " << "$" << reg2 << ", $0, $L" << label_count << endl;
			cout << "li " << "$" << reg << ", 1" << endl;                 
	        cout << "b " << "$L" << label_count+1 << endl;	
			cout << "$L" << label_count << ":"<< endl;
	        cout << "move " << "$" << reg << ", $0" << endl;
			cout << "$L" << label_count+1 << ":"<< endl;
	        label_count+=2;
			break;
		}
		case 6:
		{
			cout << "bne " << "$" << reg << ", $0, $L" << label_count << endl;
			cout << "bne " << "$" << reg2 << ", $0, $L" << label_count << endl;
			cout << "li " << "$" << reg << ", 0" << endl;                 
	        cout << "b " << "$L" << label_count+1 << endl;	
			cout << "$L" << label_count << ":"<< endl;
	        cout << "move " << "$" << reg << ", $1" << endl;
			cout << "$L" << label_count+1 << ":"<< endl;
	        label_count+=2;
			break;
		}
		case 7:
		{
			output_command("slt", reg, reg, reg2, 0);
			break;
		}
		case 8:
		{
			output_command("slt", reg, reg2, reg, 0);
			output_command("xori", reg, reg, 1, 1);
			break;
		}
		case 9:
		{
			output_command("slt", reg, reg2, reg, 0);
			break;	
		}
		case 10:
		{
			output_command("slt", reg, reg, reg2, 0);
			output_command("xori", reg, reg, 1, 1);
			break;
		}
		case 11:
		{
			output_command("xor", reg, reg, reg2, 0);
			output_command("sltu", reg, reg, 1, 1);
			break;
		}
		case 12:
		{
			output_command("xor", reg, reg, reg2, 0);
			output_command("sltu", reg, 0, reg, 0);
			break;
		}
	}
}

void float_bin_operation(int op_code){
	int freg = float_register_stack.top();
	float_register_stack.pop();
	int freg2 = float_register_stack.top();
	float_register_stack.push(freg);
	int reg = register_stack.top();

	switch(op_code){
		case 1:
			output_command("sub", freg, freg, freg2);
			break;
		case 2:
			output_command("add", freg, freg, freg2);
			break;
		case 3:
			output_command("mul", freg, freg, freg2);
			break;
		case 4:
			output_command("div", freg, freg, freg2);
			break;
		case 7:
		{
			cout << "li	$" << reg << ", 1" << endl;
			cout << "c.lt.s " << "$f"<< freg << ", $f" << freg2 << endl;
			
			cout << "bc1t $L" << label_count << endl;
			cout << "move " << "$" << reg << ", $0" << endl;
			cout << "$L" << label_count << ":" << endl;
			label_count++;
			break;
		}
		case 8:
		{
			cout << "li	$" << reg << ", 1" << endl;
			cout << "c.le.s " << "$f"<< freg << ", $f" << freg2 << endl;
			
			cout << "bc1t $L" << label_count << endl;
			cout << "move " << "$" << reg << ", $0" << endl;
			cout << "$L" << label_count << ":" << endl;
			label_count++;
			break;
		}
		case 9:
		{
			cout << "li	$" << reg << ", 1" << endl;
			cout << "c.lt.s " << "$f"<< freg2 << ", $f" << freg << endl;
			
			cout << "bc1t $L" << label_count << endl;
			cout << "move " << "$" << reg << ", $0" << endl;
			cout << "$L" << label_count << ":" << endl;
			label_count++;
			break;
		}
		case 10:
		{
			cout << "li	$" << reg << ", 1" << endl;
			cout << "c.le.s " << "$f"<< freg2 << ", $f" << freg << endl;
			
			cout << "bc1t $L" << label_count << endl;
			cout << "move " << "$" << reg << ", $0" << endl;
			cout << "$L" << label_count << ":" << endl;
			label_count++;
			break;
		}
		case 11:
		{
			cout << "li	$" << reg << ", 1" << endl;
			cout << "c.eq.s " << "$f"<< freg2 << ", $f" << freg << endl;
			
			cout << "bc1t $L" << label_count << endl;
			cout << "move " << "$" << reg << ", $0" << endl;
			cout << "$L" << label_count << ":" << endl;
			label_count++;
			break;
		}
		case 12:
		{
			cout << "li	$" << reg << ", 1" << endl;
			cout << "c.eq.s " << "$f"<< freg2 << ", $f" << freg << endl;
			
			cout << "bc1f $L" << label_count << endl;
			cout << "move " << "$" << reg << ", $0" << endl;
			cout << "$L" << label_count << ":" << endl;
			label_count++;
			break;
		}

	}
}
// print the commands
void output_command(string s, int dest, int r1, int r2, int imm){
	if(imm == 0)
		cout << s << " " << "$" << dest << ", " << "$" << r1 << ", " << "$" << r2 << endl;
	else
		cout << s << " " << "$" << dest << ", " << "$" << r1 << ", " << r2 << endl;
}

void output_command(string s, int dest, int r1, int r2){
	cout << s << ".s " << "$f" << dest << ", " << "$f" << r1 << ", " << "$f" << r2 << endl;
}

//generates initialization  code of function (implemented as an independent function as there is no ExpAst for function definitions.)
int generate_code_fn_init(string fnname){
	//Label
	cout << ".text" << endl;
	cout << fnname << ":" <<endl;

	// space needed for the local variables
	int local_stack = allocate_local_stack();
	int stack_size;
	if(local_stack == 0){
		stack_size = 8;
	}
	else{
		stack_size = 4 + local_stack; // local stack already had provision for $ra, need one more for dynamic linking 
	}

	//store return address ($31) on stack
	cout << "addiu $sp, $sp, " << -stack_size << endl;
	cout << "sw $31, " << stack_size - 4 << "($sp)" << endl;
	//set up dynamic link by saving $fp
	cout << "sw $fp, " << stack_size - 8 << "($sp)" << endl;
	cout << "addi $fp, $sp, " << stack_size - 8 << endl;
	cout << "# function initialized" << endl;
	//calee saved registers - YET TO BE IMPLEMENTED
	return stack_size;
}

//code generated at end of function
void generate_code_fn_end(int stack_size){
	// Restore calee saved registers - YET TO BE IMPLEMENTED
	// restore $sp
	cout << "# restoring function stack" <<endl;
	//cout << "move $sp, $fp" << endl;
	// restore $ra and fp
	cout << "lw $31, " << stack_size - 4 << "($sp)" << endl;
	cout << "lw $fp, " << stack_size - 8 << "($sp)" << endl;
	cout << "addiu $sp, $sp, " << stack_size << endl;
	// jump back
	cout << "j $31" << endl << endl << endl;
}

int allocate_local_stack(){
	map<string, SymRow *> :: iterator it = (localSymTab->sym_rows).begin();
	int stack_size = 0;
	while(it != (localSymTab->sym_rows).end()){
		SymRow * a = it->second;
		if(a->param_local == 0){ // checking for local variables
			int size = a->size - a->offset;
			if(size > stack_size){
				stack_size = size;
			}
		} 
		it++;
	}

	return stack_size;
}