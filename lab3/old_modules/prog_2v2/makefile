all:    Scanner.ih Scanner.h Scannerbase.h lex.cc parse.cc main.cc Parser.h Parserbase.h Parser.ih
	g++   --std=c++0x lex.cc parse.cc main.cc -o parser
	./parser < test_case.c > junk.s

        
Scanner.ih: lex.l
	if [ ! -e Scanner.ih ]; then \
		flexc++ lex.l;\
                sed -i '/include/a #include "Parserbase.h"' Scanner.ih; \
	fi

parse.cc Parser.h Parserbase.h Parser.ih: parse.y
	bisonc++  --construction parse.y;
	sed -i '/#include/a SymTab * localSymTab = new SymTab();' Parser.ih; \
	sed -i '/#include/a SymTab * globalSymTab = new SymTab();' Parser.ih; \
	sed -i '/#include/a int para_index = 1;' Parser.ih; \
	sed -i '/#include/a string ret_type;' Parser.ih; \
	sed -i '/#include/a string curr_fn;' Parser.ih; \
	sed -i '/#include/a int global_offset = 0;' Parser.ih; \
	sed -i '/#include/a int line_num = 0;' Parser.ih; \
	sed -i '/#include/a int max_stack_size = 5;' Parser.ih; \
	sed -i '/#include/a int label_count = 0;' Parser.ih; \
	sed -i '/#include/a int string_count = 0;' Parser.ih; \
	sed -i '/#include/a stack<int> register_stack;' Parser.ih; \
	sed -i '/#include/a stack<int> float_register_stack;' Parser.ih; \
	sed -i '/#include <iostream>/a #include "symcheck.h"' Parserbase.h;
	sed -i '/#include <iostream>/a #include <stack>' Parserbase.h; \
	sed -i '\|STYPE__     d_val__;| d' Parserbase.h;
	sed -i '\|typedef Meta__::SType STYPE__;| a \\tpublic: static STYPE__  d_val__; ' Parserbase.h;
	sed -i '/include "Parser.ih"/a #include "symcheck.cpp"' parse.cc;
	sed -i '\|void Parser::print__()| i Meta__::SType ParserBase::d_val__; ' parse.cc
	sed -i 's/error("Syntax error");/char err[1024];sprintf(err, "Syntax error near line \%lu", d_scanner.lineNr());error(err);/' parse.cc


.PHONY: clean     
clean:
	$(RM) Parser.ih Parser.h Parserbase.h parse.cc Scanner.ih Scanner.h Scannerbase.h lex.cc a.out graph.ps junk symtables.csv *~
