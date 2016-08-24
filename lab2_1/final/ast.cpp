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
		statement_list[i]->print();
	}
}

BIN_OP::BIN_OP(string operation, ExpAst * op1, ExpAst * op2){
	op = operation;
	operand1 = op1;
	operand2 = op2;
}

void BIN_OP::print(){
	printf("(%s ", op.c_str());
	operand1->print();
	operand2->print();
	printf(")");
}

UN_OP::UN_OP(string operation, ExpAst * op1){
	op = operation;
	operand1 = op1;
}

void UN_OP::print(){
	printf("(%s ", op.c_str());
	operand1->print();
	printf(")");
}

EXP_ASSIGN::EXP_ASSIGN(RefAst *expr, ExpAst *expr2){
	exp1 = expr;
	exp2 = expr2;
}

void EXP_ASSIGN::print(){
	printf("(Ass ");
	exp1->print();
	exp2->print();
	printf(")\n");
}

FLOAT_EXP::FLOAT_EXP(string p){
	f = p;
}

void FLOAT_EXP::print(){
	printf("(FloatConst %s)", f.c_str());
}


INT_EXP::INT_EXP(string p){
	i = p;
}

void INT_EXP::print(){
	printf("(IntConst %s)", i.c_str());
}

STRING_EXP::STRING_EXP(string p){
	s = p;
}

void STRING_EXP::print(){
	printf("(StringConst %s)", s.c_str());
}

FUNC::FUNC(string name, ExpAst *expr){
	fnname = name;
	exp = expr;
}

void FUNC::print(){
	printf("(FuncCall (Id %s)", fnname.c_str());
	exp->print();
	printf(")");
}

void EXP_GROUP::pushEx(ExpAst *expr1){
	Exp_List.push_back(expr1);
}

void EXP_GROUP::print(){
	for (int i = 0; i < Exp_List.size(); ++i){
		Exp_List[i]->print();
	}
}

void EXP_EMPTY::print(){
}

IDENTIFIER_REF::IDENTIFIER_REF(string i){
	s = i;
}

void IDENTIFIER_REF::print(){
	// printf("(Id )");
	printf("(Id '%s')", s.c_str());
}

ARRAYREF::ARRAYREF(RefAst *p, ExpAst * exp1){
	s = p;
	exp = exp1;
}

void ARRAYREF::print(){
	printf("(Array ");
	s->print();
	exp->print();
	printf(")");
}

DEREF::DEREF(RefAst *reference){
	ref = reference;
}

void DEREF::print(){
	printf("(DEREF ");
	ref->print();
	printf(")");
}

POINTER::POINTER(RefAst * reference){
	ref = reference;
}

void POINTER::print(){
	printf("(POINTER ");
	ref->print();
	printf(")");	
}

ARROW::ARROW(RefAst * reference, string i){
	ref = reference;
	s = i;
}

void ARROW::print(){
	printf("(ARROW ");
	ref->print();
	printf("(Id '%s')", s.c_str());
	printf(")");
}

MEMBER::MEMBER(RefAst * reference, string i){
	ref = reference;
	s = i;
}

void MEMBER::print(){
	printf("(MEMBER ");
	ref->print();
	printf("(Id '%s')", s.c_str());
	printf(")");
}

