
all: grammar internals arch compile_grammar lexer preprocessor libs main clean

grammar: grammar.y libs/terminal_colors.h
	bison -y -d grammar.y

internals: internals.c internals.h internals_backend.c internals_backend.h
	gcc internals.c internals.h -c
	gcc internals_backend.c -c

arch: arch/d16i/d16i.h arch/d16i/d16i.c
	gcc arch/d16i/d16i.c -c

compile_grammar: grammar.y libs/terminal_colors.h
	gcc y.tab.c -c

lexer:
	flex lexer.l
	gcc lex.yy.c -c

preprocessor: preprocessor.h preprocessor.c
	gcc preprocessor.c -c

libs: libs/file_table.c libs/file_table.h libs/symbol_table.o libs/arg_table.c libs/arg_table.h
	gcc libs/file_table.c -c
	gcc libs/symbol_table.c -c
	gcc libs/arg_table.c -c


main: main.c libs/terminal_colors.h libs/file_table.o libs/file_table.c libs/symbol_table.o libs/symbol_table.c internals.o
	gcc main.c lex.yy.o y.tab.o libs/file_table.o libs/symbol_table.o internals.o internals_backend.o d16i.o arg_table.o -g -o dasm -fno-stack-protector -z execstack -no-pie

clean:
	rm *.o
	rm *.tab.c
	rm *.yy.c