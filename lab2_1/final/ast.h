#include <string>
using namespace std;
class abstract_astnode
{
	public:
	virtual void print () = 0;
	virtual void pushAST(abstract_astnode *expr1);
	//virtual std::string generate_code(const symbolTable&) = 0;
	//virtual basic_types getType() = 0;
	//virtual bool checkTypeofAST() = 0;
	// protected:
	// virtual void setType(basic_types) = 0;
	// private:
	// typeExp astnode_type;
};

class AST_EMPTY : public abstract_astnode
{
public:
	void print();
};

class AST_GROUP : public abstract_astnode
{
private:
	std::vector<abstract_astnode *> ast_list;
public:
	void pushAST(abstract_astnode *expr1);
	void print();
};

class StmtAst : public abstract_astnode
{
public:
	virtual void print () = 0;
	virtual void pushSt(StmtAst *st);
};

class ExpAst : public abstract_astnode
{
public:
	virtual void print () = 0;
	virtual void pushEx(ExpAst *ex);
};

class RefAst : public ExpAst
{
public:
	virtual void print () = 0;
};

class EMPTY : public StmtAst
{
public:
	void print();
};

class RETN : public StmtAst
{
private:
	ExpAst * exp;
public:
	RETN(ExpAst * expr);
	void print();
};

class IF_STMT : public StmtAst
{
private:
	ExpAst * exp;
	StmtAst * stmt1;
	StmtAst * stmt2;
public:
	IF_STMT(ExpAst * expr, StmtAst *st1, StmtAst *st2);
	void print();
};

class WHILE_STMT : public StmtAst
{
private:
	ExpAst *exp;
	StmtAst *stmt;
public:
	WHILE_STMT(ExpAst *expr, StmtAst *statement);
	void print();
};

class FOR_STMT : public StmtAst
{
private:
	ExpAst *exp1;
	ExpAst *exp2;
	ExpAst *exp3;
	StmtAst *stmt;
public:
	FOR_STMT(ExpAst *expr1, ExpAst *expr2, ExpAst *expr3, StmtAst *statement);
	void print();
};

class ASSIGN : public StmtAst
{
private:
	ExpAst *exp1;
	ExpAst *exp2;
public:
	ASSIGN(ExpAst *expr, ExpAst *expr2);
	void print();
};

class BLOCK_STMT : public StmtAst
{
private:
	StmtAst *stmt;
public:
	BLOCK_STMT(StmtAst *statement);
	void print();
};

class STMT_GROUP : public StmtAst
{
private:
	std::vector<StmtAst *> statement_list;
public:
	void print();
	void pushSt(StmtAst *st);
};

class BIN_OP : public ExpAst
{
private:
	string op;
	ExpAst *operand1;
	ExpAst *operand2;
public:
	BIN_OP(string operation, ExpAst * op1, ExpAst * op2);
	void print();
};

class UN_OP : public ExpAst
{
private:
	string op;
	ExpAst *operand1;
public:
	UN_OP(string operation, ExpAst * op1);
	void print();
};

class EXP_ASSIGN : public ExpAst
{
private:
	RefAst *exp1;
	ExpAst *exp2;
public:
	EXP_ASSIGN(RefAst *expr, ExpAst *expr2);
	void print();
};

class FLOAT_EXP : public ExpAst
{
private:
	string f;
public:
	FLOAT_EXP(string p);
	void print();
};

class INT_EXP : public ExpAst
{
private:
	string i;
public:
	INT_EXP(string s);
	void print();
};

class STRING_EXP : public ExpAst
{
private:
	string s;
public:
	STRING_EXP(string p);
	void print();
};

class FUNC : public ExpAst
{
private:
	string fnname;
	ExpAst *exp;
public:
	FUNC(string name, ExpAst *expr);
	void print();
};

class POINTER : public ExpAst
{
private:
	RefAst * ref;
public:
	POINTER(RefAst * reference);
	void print();
};

class EXP_GROUP : public ExpAst
{
private:
	std::vector<ExpAst *> Exp_List;
public:
	void print();
	void pushEx(ExpAst *ex);
};

class EXP_EMPTY : public ExpAst
{
public:
	void print();
};

class IDENTIFIER_REF : public RefAst
{
private:
	string s;
public:
	IDENTIFIER_REF(string i);
	void print();
};

class ARRAYREF : public RefAst
{
private:
	RefAst * s;
	ExpAst * exp;
public:
	ARRAYREF(RefAst *p, ExpAst * exp1);
	void print();
};

class DEREF : public RefAst
{
private:
	RefAst* ref;
public:
	DEREF(RefAst *reference);
	void print();
};


class ARROW : public RefAst
{
private:
	RefAst* ref;
	string s;
public:
	ARROW(RefAst * reference, string i);
	void print();
};

class MEMBER : public RefAst
{
private:
	RefAst* ref;
	string s;
public:
	MEMBER(RefAst * reference, string i);
	void print();
};
