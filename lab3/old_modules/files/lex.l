

// There may be some flexer directives here

%%
\/\/.*\n								//skip
[ \t]                                    //skip
if										 {Parser::d_val__ = std::string (matched()); return ParserBase::IF;}
else 									 {Parser::d_val__ = std::string (matched()); return ParserBase::ELSE;}
while									 {Parser::d_val__ = std::string (matched()); return ParserBase::WHILE;}
for 									 {Parser::d_val__ = std::string (matched()); return ParserBase::FOR;}
return 								 {Parser::d_val__ = std::string (matched()); return ParserBase::RETURN;}
void									 {Parser::d_val__ = std::string (matched()); return ParserBase::VOID;}
int 									 {Parser::d_val__ = std::string (matched()); return ParserBase::INT;}
float 								 {Parser::d_val__ = std::string (matched()); return ParserBase::FLOAT;}
struct 								 {Parser::d_val__ = std::string (matched()); return ParserBase::STRUCT;}

[[:alpha:]][[:alnum:]|"_"]*					 {Parser::d_val__ = std::string (matched()); return ParserBase::IDENTIFIER;}

([0-9]+[.][0-9]*(([eE][+-]?)?[0-9]+)?)|([0-9]*[.][0-9]+(([eE][+-]?)?[0-9]+)?)			 {Parser::d_val__ = std::string (matched()); return ParserBase::FLOAT_CONSTANT;}
([1-9][0-9]*)|(0[bB][01]+)|(0[0-7]*)|(0[xX][0-9a-fA-F]+) 						 {Parser::d_val__ = std::string(matched()); return ParserBase::INT_CONSTANT;}
\"[^\\"]*([\\][\\tn"][^\\"]*)*\"												 {Parser::d_val__ = std::string (matched()); return ParserBase::STRING_LITERAL;}

"=="										 {Parser::d_val__ = std::string (matched()); return ParserBase::EQ_OP;}
"<="										 {Parser::d_val__ = std::string (matched()); return ParserBase::LE_OP;}
">="										 {Parser::d_val__ = std::string (matched()); return ParserBase::GE_OP;}
"!="										 {Parser::d_val__ = std::string (matched()); return ParserBase::NE_OP;}
"&"											return '&';
"&&"										 {Parser::d_val__ = std::string (matched()); return ParserBase::AND_OP;}
"||"										 {Parser::d_val__ = std::string (matched()); return ParserBase::OR_OP;}
"++"										 {Parser::d_val__ = std::string (matched()); return ParserBase::INC_OP;}
"<"											return '<';
">"											return '>';

"*"											return '*';
"/"											return '/';
"+"                                         return '+';
"-"											return '-';

"="                                         return '=';
","                                         return ',';
"("                                         return '(';
")"                                         return ')';
"["											return '[';
"]"											return ']';
"{"											return '{';
"}"											return '}';
"!"											return '!';
":"                                         return ':';
";"                                         return ';';
"."											return '.';
"->"										{Parser::d_val__ = std::string (matched()); return ParserBase::PTR_OP;}
"\n"                                        
"\r"                                        
.                                           {Parser::d_val__ = std::string (matched()); return ParserBase::OTHERS;}                                         
