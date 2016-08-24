

// There may be some flexer directives here

%%
[ \t]                                    //skip
IF|if										return IF;
ELSE|else 									return ELSE;
WHILE|while									return WHILE;
FOR|for 									return FOR;
RETURN|return 								return RETURN;
VOID|void									return VOID;
INT|int 									return INT;
FLOAT|float 								return FLOAT;

[[:alpha:]][[:alnum:]|"_"]*					return IDENTIFIER;

([0-9]+"."[0-9]*([eE][+-]?)?[0-9]*)|([0-9]*"."[0-9]+([eE][+-]?)?[0-9]*)			return FLOAT_CONSTANT;
([1-9][0-9]*)|(0[bB][01]*)|(0[0-7]*)|(0[xX][0-9a-fA-F]*) 						return INT_CONSTANT;
\"[^\\"]*([\\][\\tn"][^\\"]*)*\"												return STRING_LITERAL;

"=="										return EQ_OP;
"<="										return LE_OP;
">="										return GE_OP;
"!="										return NE_OP;
"&&"										return AND_OP;
"||"										return OR_OP;
"++"										return INC_OP;
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
"\n"                                        
"\r"                                        
.                                           return OTHERS;                                         
