ARCH=d32i



all: backend grammar internals arch compile_grammar lexer preprocessor libs main clean

backend: backend/Makefile
	@$(MAKE) -C backend/
	./backend/backend_gen arch/${ARCH}/$(ARCH).id -p arch/$(ARCH)/

grammar: grammar.y libs/terminal_colors.h
	bison -y -d grammar.y

internals: internals.c internals.h internals_backend.c internals_backend.h
	gcc internals.c internals.h -c
	gcc internals_backend.c -c

arch: arch/$(ARCH)/$(ARCH).h arch/$(ARCH)/$(ARCH).c
	gcc arch/$(ARCH)/$(ARCH).c -c

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
	gcc main.c lex.yy.o y.tab.o libs/file_table.o libs/symbol_table.o internals.o internals_backend.o d16i.o arg_table.o -g -o dasm

clean:
	rm *.o
	rm *.tab.c
	rm *.yy.
	arch/$(d32i)/target.*
