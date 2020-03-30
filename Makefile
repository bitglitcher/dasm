
all: grammar lexer preprocessor libs main clean

grammar: grammar.y libs/terminal_colors.h
	bison -y -d grammar.y
	gcc y.tab.c -c

lexer:
	flex lexer.l
	gcc lex.yy.c -c

preprocessor: preprocessor.h preprocessor.c
	gcc preprocessor.c -c

libs: libs/file_table.c libs/file_table.h libs/symbol_table.o
	gcc libs/file_table.c -c
	gcc libs/symbol_table.c -c
	
main: main.c libs/terminal_colors.h libs/file_table.o libs/file_table.c libs/symbol_table.o libs/symbol_table.c
	gcc main.c lex.yy.o y.tab.o libs/file_table.o libs/symbol_table.o -g -o dasm

clean: lex.yy.o y.tab.o
	rm lex.yy.o y.tab.o libs/file_table.o