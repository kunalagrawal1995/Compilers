#include <string>
#include <map>
#include <set>
#include "ast.h"
using namespace std;
class var_type{
public:
	string t;
	var_type * type;
	var_type();
	var_type(string s);
};

class SymTab;

class SymRow{
public:
	string symName; 	// for symbol name
	int var_fun;		// 1 -> func, 0 -> var, 2 -> struct
	int param_local;	// -1 -> global, 0 -> local, i -> ith parameter; >= 1 if it exists  
	var_type * head;
	var_type * tail;
	int size;
	int offset;
	SymTab *symTab;		// location for the symbol table
	SymRow(string inp_symName, int inp_var_fun, int int_param_local, string inp_type, SymTab * symTable);
	SymRow();
	void print_row();
};

class SymTab{
public:
	int insertRow(string name, SymRow * s);
	map <string, SymRow *> sym_rows;
	void print_table();
};

// get type of the var, recusively called
string get_type(var_type * head, string s);

// type when as it appears as l_expression i.e. int a[10] is of int[10] type
string get_ltype(var_type * head, string s);

// get the pointers, arrays foloowing the base type
string rem_base_type(string type);

// get base type i.e. int, float, void, struct
string base_type(string type);

// get the size, removing all array indices
int get_base_size(var_type * base);

// return true if the type is a struct only type and not a pointer or array or anything
bool is_struct(var_type * type);

// return type for a binary operator
// (&&,||) -> 0; 
// (==) -> 1; 
// (<,<=,>=,>) -> 2; 
// (+) -> 3; 
// (-) -> 4;  
// (*,/) -> 5; 
var_type* result_type(var_type * left, var_type * right, int op_type); 

//return type of dereferenced variable
var_type* deref(var_type * type);

//returns type of referenced variable
var_type* ref(var_type * type);

//returns type for unary operator not
var_type* unary_not(var_type * type);

// returns type of the unary operator minus
var_type* unary_minus(var_type * type);

//return type of identifier; throws error if undeclared identifier
var_type* identifier_type(string id);

//returns type of struct member access
// access_type is 0 for . access, 1 for -> access
var_type* data_member_access(var_type * type, string data_member, int access_type);

vector<SymRow *> get_parameters(SymTab *fn_symTab);

// returns true if the left and the right type are compatible; can be passed on as parameters
bool type_match(var_type *left, var_type *right);

// checks whether the given list of expressions can be passed to the function or not
int function_parameter_match(string fn_name, vector<ExpAst *> Exp_List);

// checks if the right expression can be assigned to the left; where left is the var type of the left_expression
var_type* valid_assign(var_type *left, ExpAst *right);

// 2 for casting operator to float, 1 for int, 1 for pointer involved(currently the operator for them is being casted to int) 
int casting_binary(ExpAst *left, ExpAst * right);

void casting_assign(var_type * to, ExpAst * from);

// printing symtabs and asts
// the symtab is redirected to symtables.csv
// the asts are printed in the std out
void print_symtab_ast();
