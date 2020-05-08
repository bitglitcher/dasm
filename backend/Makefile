all:
	bison -d grammar.y --report=all
	flex lexer.l
	gcc lex.yy.c grammar.tab.c

clean:
	rm grammar.tab.c
	rm grammar.tab.h
	rm lex.yy.c
	rm grammar.output
	rm a.out
