all:
	bison -d grammar.y --report=all
	flex lexer.l
	gcc lex.yy.c grammar.tab.c