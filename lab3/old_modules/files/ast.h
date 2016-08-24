#include <string>
using namespace std;

class var_type;

class abstract_astnode
{
	public:
	virtual void print () = 0;
	virtual void pushAST(abstract_astnode *expr1);
	var_type * type;
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
	bool ltype; 	// to be set true when the the symbols can never be part of ltype, & can be in (*(&i) = i ALLOWED), while operators like +,-,> others cant
	bool to_cast;	// whether the expression needs to be typecasted
	string cast;	// the format in which you need to cast
	int int_value; 	// the value resulting from calculating the expression
	bool only_int;	// the sub-expression consists of only int constants
	
	// CODE GENERATION, Current assumption that all the addresses(var local and global, and array references can be obtained by using at most register or can be loaded from memory, their overhead is ignored, AT THE MOMENT) 
	int label; // min number of registers required so as to make sure that the no storing in the subtree would be required
	// parent is passed for optimizing the clusters, and using the commutativity, it returns the vector of the expression trees, so that they can be scheduled appropriately
	virtual int calculate_label(int parent, int is_left) = 0;  
	// make this virtual once all the children have the implementation
	virtual void generate_code(int n) = 0;
	// this function is used to get the types to claculate size, for array address resolution
	// virtual var_type* get_type() = 0;

	virtual void print () = 0;
	virtual void pushEx(ExpAst *ex);
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

class EXPR_STMT : public StmtAst
{
private:
	ExpAst *exp;
public:
	EXPR_STMT(ExpAst *expr);
	void print();	
};

class BIN_OP : public ExpAst
{
private:
	string op;
	ExpAst *operand1;
	ExpAst *operand2;
public:
	int calculate_label(int parent, int is_left);  
	BIN_OP(string operation, ExpAst * op1, ExpAst * op2);
	// var_type* get_type();
	void generate_code(int n);
	void print();
};

class UN_OP : public ExpAst
{
private:
	string op;
	ExpAst *operand1;
public:
	int calculate_label(int parent, int is_left);  
	UN_OP(string operation, ExpAst * op1);
	// var_type* get_type();
	void generate_code(int n);
	void print();
};

//Assignment is now an expression only. unary_exp = exp
class EXP_ASSIGN : public ExpAst
{
private:
	ExpAst *exp1;
	ExpAst *exp2;
public:
	int calculate_label(int parent, int is_left);  
	EXP_ASSIGN(ExpAst *expr, ExpAst *expr2);
	// var_type* get_type();
	void generate_code(int n);
	void print();
};

class FLOAT_EXP : public ExpAst
{
private:
	string f;
public:
	int calculate_label(int parent, int is_left);  
	FLOAT_EXP(string p);
	// var_type* get_type();
	void generate_code(int n);
	void print();
};

class INT_EXP : public ExpAst
{
private:
	string i;
public:
	int calculate_label(int parent, int is_left);  
	INT_EXP(string s);
	// var_type* get_type();
	void generate_code(int n);
	void print();
};

class STRING_EXP : public ExpAst
{
private:
	string s;
public:
	int calculate_label(int parent, int is_left);  
	STRING_EXP(string p);
	// var_type* get_type();
	void generate_code(int n);
	void print();
};

class FUNC : public ExpAst
{
private:
	string fnname;
	ExpAst *exp;
public:
	int calculate_label(int parent, int is_left);  
	FUNC(string name, ExpAst *expr);
	// var_type* get_type();
	void generate_code(int n);
	void print();
};

class EXP_GROUP : public ExpAst
{
private:
	std::vector<ExpAst *> Exp_List;
public:
	int calculate_label(int parent, int is_left);  
	void print();
	void pushEx(ExpAst *ex);
	// var_type* get_type();
	void generate_code(int n);
	std::vector<ExpAst *> get_expression_list();
};

class EXP_EMPTY : public ExpAst
{
public:
	void generate_code(int n);
	void print();
	// var_type* get_type();
	int calculate_label(int parent, int is_left);  
};

class IDENTIFIER_REF : public ExpAst
{
private:
	string s;
public:
	int calculate_label(int parent, int is_left);  
	IDENTIFIER_REF(string i);
	// var_type* get_type();
	void generate_code(int n);
	void print();
};

class ARRAYREF : public ExpAst
{
private:
	ExpAst * s;
	ExpAst * exp;
public:
	int calculate_label(int parent, int is_left);  
	ARRAYREF(ExpAst *p, ExpAst * exp1);
	// var_type* get_type();
	void generate_code(int n);
	void print();
};

class ARROW : public ExpAst
{
private:
	ExpAst* ref;
	string s;
public:
	int calculate_label(int parent, int is_left);  
	ARROW(ExpAst * reference, string i);
	// var_type* get_type();
	void generate_code(int n);
	void print();
};

class MEMBER : public ExpAst
{
private:
	ExpAst* ref;
	string s;
public:
	int calculate_label(int parent, int is_left);  
	MEMBER(ExpAst * reference, string i);
	// var_type* get_type();
	void generate_code(int n);
	void print();
};
	
int get_size(var_type* t);

// n is the number of registers alloted, currently working on int
void init_stack(int n);

// this will just swap the top two registers
void swap_register_stack();

// given two expressions, the stack is global how to evaluate the expressions
void manage_expr(ExpAst *expr1, ExpAst *expr2, int arr); 

// convert the string to op_code
int get_op_code(string s);

// apply the given operation
void bin_operation(int op_code);

// print the commands
void output_command(string s, int dest, int r1, int r2, int imm);

