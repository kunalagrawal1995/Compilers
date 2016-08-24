#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "ast.cpp"

void print_error(int err_code, string s){
	string pre = "ERROR at line " + to_string(line_num) + ": ";
	switch(err_code){
		case -1:
			cerr << pre << "variable " + s + " redeclared" <<endl;
			break;
		case -2:
			cerr << pre << "variable declared as void" <<endl;
			break;
		case -3:
			cerr << pre << s <<endl;
			break;
		case -5:
			cerr << pre << "array indices are not integer" << endl;
			break;
		case -6:
			cerr << pre << "array indices are negative" << endl;
			break;
		case -7:
			cerr << pre << "type 'struct " + s + "' not defined" << endl;
			break;
		case -11:
			cerr << pre << "used struct type value where scalar is required" << endl;
			break;
		case -15:
			cerr << pre << "invalid operands to binary " + s << endl;
			break;
		case -21:
			cerr << pre << "dereferencing 'void *' pointer" <<endl;
			break;
		case -22:
			cerr << pre << "invalid type to unary '*'" <<endl;
			break;
		case -23:
			cerr << pre << "label used but not defined" <<endl;
			break;
		case -24:
			cerr << pre << "wrong type argument to unary exclamation mark" <<endl;
			break;
		case -25:
			cerr << pre << "wrong type argument to unary minus" <<endl;
			break;
		case -26:
			cerr << pre << "wrong type argument to increment" <<endl;
			break;
		case -31:
			cerr << pre << "request for member '" + s + "' in something which is not a struct" <<endl;
			break;
		case -32:
			cerr << pre << "invalid type argument of ‘->’ (have ‘" + s + "’)" <<endl;
			break;
		case -33:
			cerr << pre << s <<endl;
			break;
		case -34:
			cerr << pre << "dereferencing pointer to incomplete type" <<endl;
			break;
		case -51:
			cerr << pre << "undefined reference to " + s << endl;
			break;
		case -52:
			cerr << pre << "too few arguments to function '" + s + "'" << endl;
			break;
		case -53:
			cerr << pre << "too many arguments to function '" + s + "'" << endl;
			break;
		case -54:
			cerr << pre << s << endl;
			break;
		case -55:
			cerr << pre << "called object ‘" + s + "’ is not a function or function pointer" << endl;
			break;
		case -61:
			cerr << pre << "lvalue required as left operand of assignment" << endl;
			break;
		case -62:
			cerr << pre << "incompatible types when assigning to type " + s << endl;
			break;
		case -63:
			cerr << pre << "void value not ignored as it ought to be" << endl;
			break;
		case -64:
			cerr << pre << "lvalue required as '&' operand" << endl;
			break;
		case -65:
			cerr << pre << "lvalue required as increment operand" << endl;
			break;
		case -71:
			cerr << pre << "incompatible return types" << endl;
			break;	
		default:
			cerr << "dude, you forgot to include an error code print"<<endl;
			break;
	}
	exit(0);
}

var_type::var_type(){
	t = "";
	type = NULL;
}

var_type::var_type(string s){
	t = s;
	type = NULL;
}

SymRow::SymRow(){
	var_fun = 0;	//0 -> variable by default
}

void SymRow::print_row(){
 	std::cout << symName <<"\t"<<var_fun<<"\t"<<param_local<<"\t"<<get_type(head, "") <<"\t"<<size << "\t" << offset<<endl;
}

void SymTab::print_table(){
	map<string, SymRow *> :: iterator beg = sym_rows.begin();
	while(beg != sym_rows.end()){
		(beg->second)->print_row();
		beg++;
	}
}

int SymTab::insertRow(string name, SymRow * s){
	if(sym_rows.find(name) == sym_rows.end()){
		sym_rows.insert(make_pair(name, s));
		return 0;
	}
	else{
		return -1;
	}
}

// get type of the var, recusively called
string get_type(var_type * head, string s){
	if(head == NULL)
		return s;
	if(head->type == NULL){
		return head->t + s;
	}
	else{
		if(s == ""){
			s = "*";
			return get_type(head->type, s);
		}
		else{
			s = s + "[" + head->t + "]";
			return get_type(head->type, s);
		}
	}
}

// type when as it appears as l_expression i.e. int a[10] is of int[10] type
string get_ltype(var_type * head, string s){
	if(head == NULL)
		return s;
	if(head->type == NULL){
		return head->t + s;
	}
	else{
		s = s + "[" + head->t + "]";
		return get_type(head->type, s);
	}
}

// get the pointers, arrays foloowing the base type
string rem_base_type(string type){
	switch(type[0]){
		case 'i':
			return type.substr(3, type.length());
			break;
		case 'v':
			return type.substr(4, type.length());
			break;
		case 'f':
			return type.substr(5, type.length());
			break;		
		case 's':
			int i;
			for(i = 0; i<type.length(); ++i){
				if(type[i] == '*'){
					break;
				}
			}
			// i stores index of first appearance of *
			return type.substr(i, type.length());
			break;
		case 'c':
			return type.substr(4, type.length());			
	}
}

// get base type i.e. int, float, void, struct
string base_type(string type){
	switch(type[0]){
		case 'i':
			return "int";
			break;
		case 'v':
			return "void";
			break;
		case 'f':
			return "float";
			break;		
		case 's':
			int i;
			for(i = 0; i<type.length(); ++i){
				if(type[i] == '*'){
					break;
				}
			}
			// i stores index of first appearance of *
			return type.substr(0, i);
			break;	
		case 'c':
			return "char";
			break;		
	}
}

// get the size, removing all array indices
int get_base_size(var_type * base){
	string t = get_type(base, "");
	if(t[t.length()-1] == '*') // its a pointer, not need to check whether the struct is declared or not
		return 8;
	// following cases when its not pointer
	if(t[0] == 'i')
		return 4;
	if(t[0] == 'f')
		return 4;
	if(t[0] == 'v')
		return 1;
	if(t[0] == 's'){
		string str_name = t; // getting the struct name; 
		map<string, SymRow *> :: iterator it = (globalSymTab->sym_rows).find(str_name);
		if(it == (globalSymTab->sym_rows).end()){
			print_error(-7, str_name);
		}
		else{
			return (it->second)->size;
		}
	}
	return 1; // for char 
}

// return true if the type is a struct only type and not a pointer or array or anything
bool is_struct(var_type * type){
	string type1 = get_type(type, "");	
	string rem_type = rem_base_type(type1);	
	if(type1[0] != 's')
		return false;
	else{
		if(rem_type.length() != 0)
			return false;
		else
			return true;
	}
}

// return type for a binary operator
// (&&,||) -> 0; 
// (==) -> 1; 
// (<,<=,>=,>) -> 2; 
// (+) -> 3; 
// (-) -> 4;  
// (*,/) -> 5; 
var_type* result_type(var_type * left, var_type * right, int op_type){
	string type1 = get_type(left, "");
	string type2 = get_type(right, "");
	string rem_type1 = rem_base_type(type1);
	string rem_type2 = rem_base_type(type2);
	bool is_struct_left = is_struct(left);
	bool is_struct_right = is_struct(right);

	switch(op_type){
		case 0:
			if(!is_struct_left && !is_struct_right){
				return new var_type("int");
			}
			else{
				print_error(-11, "");	// -11 for when the opernad is struct
			}
			break;
		case 5:
			if(rem_type1.length() == 0 && rem_type2.length() == 0 && !is_struct_left && !is_struct_right){
				// none of the operands are pointers and neither they are struct
				if(type1 == "float"){
					return new var_type("float");
				}
				else{
					return new var_type(type2);
				}
			}
			else{
				print_error(-15, "operator ( have '" + type1 + "' and '" + type2 + "' )");	// -12 for *,/
			}
			break;
		case 2:
			if(!is_struct_right && !is_struct_left){
				if(rem_type1.length() == 0 && rem_type2.length() == 0){ // base types here
					return new var_type("int");
				}
				else if(type1 == type2){	// pointers but of same type;
					return new var_type("int");
				}
				else{
					print_error(-15, "operator ( have '" + type1 + "' and '" + type2 + "' )"); // error with the operands 
				}
			}
			else{
					print_error(-15, "operator ( have '" + type1 + "' and '" + type2 + "' )"); // giving struct as operand 
			}
			break;
		case 3:
			if(!is_struct_left && !is_struct_right){
				if(rem_type1.length() == 0 && rem_type2.length() == 0){ // base_types
					if(type1 == "float"){
						return new var_type("float");
					}
					else{
						return new var_type(type2);
					}
				}
				else{
					if(type1 == "int"){ // right in this case will be a pointer
						return right;
					}
					else if(type2 == "int"){
						return left;
					}
					else{
						print_error(-15, "+( have '" + type1 + "' and '" + type2 + "' )"); // mismatch in operands for binary operator +
					// invalid operators to binany
					}
				}
			}
			else{
				print_error(-15, "+( have '" + type1 + "' and '" + type2 + "' )"); // struct thingy
			}
			break;
		case 4:
			if(!is_struct_left && !is_struct_right){
				if(rem_type1.length() == 0 && rem_type2.length() == 0){ // base_types
					if(type1 == "float"){
						return new var_type("float");
					}
					else{
						return new var_type(type2);
					}
				}
				else{
					if(type2 == "int"){ // subtracting a int from a pointer
						return left;
					}
					else if(type2 == type1){	// subtracting same types return offset
						return new var_type("int");
					}
					else{
						print_error(-15, "-( have '" + type1 + "' and '" + type2 + "' )"); // mismatch in operands for binary operator +
					// invalid operators to binany
					}
				}
			}
			else{
				print_error(-15, "+( have '" + type1 + "' and '" + type2 + "' )"); // struct thingy
			}
			break;
		case 1:
			if(!is_struct_right && !is_struct_left){
				if(rem_type1.length() == 0 && rem_type2.length() == 0){ // base types here
					return new var_type("int");
				}
				else if(type1 == type2){	// pointers but of same type;
					return new var_type("int");
				}
				else if((type1 == "void*" && rem_type2.length() != 0) || (type2 == "void*" && rem_type1.length() != 0)){ // both are pointers/arays and one is void*
					return new var_type("int"); 
				}
				else{
					print_error(-15, "operator ( have '" + type1 + "' and '" + type2 + "' )");
				}
			}
			else{
					print_error(-15, "+( have '" + type1 + "' and '" + type2 + "' )"); // giving struct as operand 
			}
			break;
	}
}

//return type of dereferenced variable
var_type* deref(var_type * type){
	if(type->type != NULL){															// with array indices
		return type->type;
	}
	else{
		string type_base_pointer = type->t;
		if(type_base_pointer[type_base_pointer.length()-1] == '*'){					// without array pointers
			var_type *deref_type = new var_type((type_base_pointer).substr(0, type_base_pointer.length()-1));
			if(deref_type->t != "void"){
				return deref_type;
			}	
			else{
				print_error(-21, ""); 													// dereferencing to a void 
			}
		}
		else{
			print_error(-22, "(have '" + type_base_pointer + "')");						// cannot deref a base type
		}
	}
}

//returns type of referenced variable
var_type* ref(var_type * type){
	if(type->t != "ref"){
		var_type *ref_type = new var_type("ref");
		ref_type->type = type;
		return ref_type;	
	}
	else{
		print_error(-23, "");															// referencing a referenced variable
	}
}

//returns type for unary operator not
var_type* unary_not(var_type * type){
	if(is_struct(type)){
		print_error(24, "");
	}
	else{
		return new var_type("int");
	}
} 

// returns type of the unary operator minus
var_type* unary_minus(var_type *type){
	string str_type = get_type(type, "");
	string rem_type = rem_base_type(str_type);
	if(is_struct(type) || rem_type.length() != 0){	// is its a struct or a pointer 
		print_error(-25, "");
	}
	else{
		return type;
	}
}

//return type of identifier; throws error if undeclared identifier
var_type* identifier_type(string id){
	map<string, SymRow *> :: iterator var = localSymTab->sym_rows.find(id);
        if(var == localSymTab->sym_rows.end()) {
            print_error(-3, "variable '" + id + "' undeclared");                        //undeclared variable
        }
        else{
            return (var->second)->head;
        }
}

//returns type of struct member access
// access_type is 0 for . access, 1 for -> access 
var_type* data_member_access(var_type * type, string data_member, int access_type){
	string type_str = get_type(type, "");
	string bs_type = base_type(type_str);
	string rem = rem_base_type(type_str);
	if(type_str.substr(0,6) != "struct"){
		print_error(-31, data_member);					//request for member in something which is not a struct
	}

	if((access_type == 0 && rem == "") || (access_type == 1 && rem == "*")){
		//lookup in struct's symbol table
		map<string, SymRow *> :: iterator struct_symrow = globalSymTab->sym_rows.find(bs_type);
		if(struct_symrow == globalSymTab->sym_rows.end()){
			print_error(-34, "");
		}
		SymTab* struct_symtab = (struct_symrow->second)->symTab;	//symbol table of struct
		map <string, SymRow *> :: iterator var = struct_symtab->sym_rows.find(data_member);
		if(var == struct_symtab->sym_rows.end()){
			print_error(-33, "'" + type_str + "' has no member named '" + data_member +"'");	//non-defined data member access attempt
		}
		else{
			return (var->second)->head;
		}
	}
	else{
		if(access_type == 1 && rem == ""){
			print_error(-32, type_str);
		}
		else{
			print_error(-31, data_member);
		}
	}
}

vector<SymRow *> get_parameters(SymTab *fn_symTab){
	map<int, SymRow*> param;
	map<string, SymRow*> :: iterator it = (fn_symTab->sym_rows).begin();
	while(it != fn_symTab->sym_rows.end()){
		if((it->second)->param_local > 0){
			param.insert(make_pair((it->second)->param_local, it->second));
		}
		it++;
	}
	vector<SymRow *> parameters;
	map<int, SymRow*> :: iterator par = param.begin();
	while(par != param.end()){
		parameters.push_back(par->second);
		par++;
	}
	return parameters;
}

// returns true if the left and the right type are compatible; can be passed on as parameters
bool type_match(var_type *left, var_type *right){
	string type1 = get_type(left, "");
	string type2 = get_type(right, "");
	string rem_type1 = rem_base_type(type1);
	string rem_type2 = rem_base_type(type2);
	if(!(type1[0] == 's' || type2[0] == 's')){										// when the types are not structs or pointers involving struct	
		if(rem_type1.length() == rem_type2.length() && rem_type1.length() == 0 && type1[0] != 'v'){ 	// handelling base types: int and float, the left base type should be void	
			return true;
		}
		else{																		// one of the types involve pointer
			if(type1 == type2)
				return true;										
			else if((type1 == "void*" && rem_type2.length() != 0) || (type2 == "void*" && rem_type1.length() != 0)){ // both are pointers/arays and one is void*
				return true; 
			}
			else 
				return false;
		}
	}
	else{
		if(type1 == type2){
			return true;
		}	// exactly same types allowed
		else if((type1 == "void*" && rem_type2.length() != 0) || (type2 == "void*" && rem_type1.length() != 0)){ // both are pointers/arays and one is void*
			return true; 
		}
		else
			return false;
	}
}

// checks whether the given list of expressions can be passed to the function or not
int function_parameter_match(string fn_name, vector<ExpAst *> Exp_List){
	map<string, SymRow *> :: iterator fn_pointer = localSymTab->sym_rows.find(fn_name);
	if(fn_pointer != localSymTab->sym_rows.end()){
		print_error(-55, fn_name);	// locally declared variable used as function
	}

	fn_pointer = (globalSymTab->sym_rows.find(fn_name));
	if(fn_pointer == globalSymTab->sym_rows.end()){
		print_error(-51, fn_name);	// check the error message if the function name not found
	}

	SymTab* fn_symTab = (fn_pointer->second)->symTab;
	vector<SymRow *> parameter_list = get_parameters(fn_symTab);

	// matching the number of parameters
	if(parameter_list.size() > Exp_List.size()){
		print_error(-52, fn_name);	// error about number of arguments mismatch
	}
	else if(parameter_list.size() < Exp_List.size()){
		print_error(-53, fn_name);	// error about number of arguments mismatch
	}

	for (int i = 0; i < parameter_list.size(); ++i){
		if(!type_match(parameter_list[i]->head, Exp_List[i]->type)){
			print_error(-54, "Expected '" + get_type(parameter_list[i]->head, "") + "' but argument is of type '" + get_type(Exp_List[i]->type, "") + "'");	// error mismatch on the index i
		}
		else{
			casting_assign(parameter_list[i]->head, Exp_List[i]); // casting if required
		}
	}
	return 1;
}

// checks if the right expression can be assigned to the left; where left is the var type of the left_expression
var_type* valid_assign(var_type *left, ExpAst *right_expr){
	var_type * right = right_expr->type;
	if(left->t == "ref"){
		print_error(-61, ""); // assigning to an reference
	}
	if(left->type != NULL){
		print_error(-62, "'" + get_ltype(left, "") + "' from type '" + get_type(right, "") + "'"); // array assignment
	}

	if(right->t == "void"){
		print_error(-63, "");
	}
	string type_t = left->t;

	if(type_t[type_t.length()-1] == '*' && right_expr->only_int && right_expr->int_value == 0){	// special case where we assigning 0 to pointers is allowed
		return left;
	} 

	if(type_match(left, right)){	// do compatiblity check
		return left;
	}
	else{
		print_error(-62, "'" + get_type(left, "") + "' from type '" + get_type(right, "") + "'"); // errorneous assignment
	}
}

// 2 for casting operator to float, 1 for int, 1 for pointer involved(currently the operator for them is being casted to int) 
int casting_binary(ExpAst * left, ExpAst * right){
	string type1 = get_type(left->type, "");
	string type2 = get_type(right->type, "");
	string rem1 = rem_base_type(type1);
	string rem2 = rem_base_type(type2);
	if(rem1.length() == 0 && rem2.length() == 0 && !is_struct(left->type) && !is_struct(right->type)){ // base types
		if(type1 != type2){
			if(type1 == "float"){
				left->to_cast = false;
				right->to_cast = true;
				right->cast = "FLOAT";
				return 2;
			}
			else{
				right->to_cast = false;
				left->to_cast = true;
				left->cast = "FLOAT";
				return 2;
			}
		}
		else{
			if(type1 == "float"){
				right->to_cast = false;
				left->to_cast = false;
				return 2;
			}
			else{
				right->to_cast = false;
				left->to_cast = false;
				return 1;
			}
		}
	}
	else{
		right->to_cast = false;
		left->to_cast = false;
		return 1; // cast to int for pointers
	}
}

void casting_assign(var_type * to, ExpAst *from){
	string type1 = get_type(to, "");
	string type2 = get_type(from->type, "");
	string rem1 = rem_base_type(type1);
	string rem2 = rem_base_type(type2);
	string cast;
	if(type1[0] == 'i')
		cast = "INT";

	if(type1[0] == 'f')
		cast = "FLOAT";
	
	if(rem1.length() == 0 && rem2.length() == 0 && !is_struct(to) && !is_struct(from->type)){ // base types
		if(type1 != type2){
			from->to_cast = true;
			from->cast = cast;
		}
	}
}

// printing symtabs and asts
// the symtab is redirected to symtables.csv
// the asts are printed in the std out
void print_symtab_ast(){
    //Ref: http://stackoverflow.com/questions/10150468/how-to-redirect-cin-and-cout-to-files
    //redirect cout to the file symtables.csv
    std::ofstream out("symtables.csv");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf());

	cout<<"Global Symbol Table"<<endl;
	cout<<"symbol_name\tvar_fun_struct\tparam_local\ttype\tsize\toffset"<<endl;
	globalSymTab->print_table();
	cout<<endl<<endl;

	SymTab *fun_str_symtab;
	map<string, SymRow *> :: iterator beg = globalSymTab->sym_rows.begin();
	while(beg != globalSymTab->sym_rows.end()){
		if((beg->second)->symTab != NULL){
			cout<<"Local Symbol Table for "<<(beg->second)->symName<<endl;
			cout<<"symbol_name\tvar_fun_struct\tparam_local\ttype\tsize\toffset"<<endl;
			((beg->second)->symTab)->print_table();
			cout<<endl;
		}
			beg++;
	}

    std::cout.rdbuf(coutbuf); //reset to standard output again
}