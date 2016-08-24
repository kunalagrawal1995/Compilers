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
	op = operation;
	operand1 = op1;
	operand2 = op2;
}

void BIN_OP::print(){
	if(to_cast){
		printf("(TO-%s",cast.c_str());
	}
	printf("(%s ", op.c_str());
	operand1->print();
	operand2->print();
	printf(")");
	if(to_cast){
		printf(")");
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
	printf("(%s ", op.c_str());
	operand1->print();
	printf(")");
	if(to_cast){
		printf(")");
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

void EXP_EMPTY::print(){
}

IDENTIFIER_REF::IDENTIFIER_REF(string i){
	to_cast = false;
	s = i;
}

void IDENTIFIER_REF::print(){
	if(to_cast){
		printf("(TO-%s",cast.c_str());
	}
	printf("(Id '%s')", s.c_str());
	if(to_cast){
		printf(")");
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

DEREF::DEREF(RefAst *reference){
	to_cast = false;
	ref = reference;
}

void DEREF::print(){
	if(to_cast){
		printf("(TO-%s",cast.c_str());
	}
	printf("(DEREF ");
	ref->print();
	printf(")");
	if(to_cast){
		printf(")");
	}
}

POINTER::POINTER(RefAst * reference){
	to_cast = false;
	ref = reference;
}

void POINTER::print(){
	if(to_cast){
		printf("(TO-%s",cast.c_str());
	}
	printf("(POINTER ");
	ref->print();
	printf(")");	
	if(to_cast){
		printf(")");
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

