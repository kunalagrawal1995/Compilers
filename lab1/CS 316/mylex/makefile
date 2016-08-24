all:    Parser.ih Parser.h Parserbase.h parse.cc Scanner.ih Scanner.h Scannerbase.h lex.cc  main.cc
	g++   --std=c++0x lex.cc parse.cc main.cc -o parser;
	echo "digraph G {ordering=out;\n\n""`./parser < test.cc`""}" > graph.dot
	dot -Tpdf graph.dot -o graph.pdf
#	ps2pdf graph.ps
#	egrep 'nextToken|reduce' junk
        
Parser.ih: parse.y 
	if [ ! -e Parser.ih ]; then \
		bisonc++ --construction -V parse.y && sed -i '/#include/a int nodeCount = 0;' Parser.ih; \
	fi

Parser.h Parserbase.h parse.cc:  parse.y
	bisonc++ --construction -V parse.y;

Scanner.ih: lexical.l Parserbase.h
	flexc++ lexical.l;
	sed -i '/include/a #include "Parserbase.h"' Scanner.ih;

Scanner.h Scannerbase.h lex.cc: lexical.l
	flexc++ lexical.l; 

.PHONY: clean     
clean:
	$(RM) Parser.ih Parser.h Parserbase.h parse.cc Scanner.ih Scanner.h Scannerbase.h lex.cc a.out graph.ps junk *~