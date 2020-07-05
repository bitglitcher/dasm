ARCH=d32i

all: backend grammar internals arch compile_grammar lexer preprocessor libs main

backend: backend/*
	@$(MAKE) -C backend/
	$(Creating Build Directory)
ifeq (,$(wildcard build/))
	mkdir build
endif
	./backend/backend_gen arch/${ARCH}/$(ARCH).id -p build/





grammar: grammar.y libs/terminal_colors.h
	bison -y -d grammar.y

internals: internals.c internals.h internals_backend.c internals_backend.h
	gcc internals.c internals.h -c
	gcc internals_backend.c -c

arch: build/target.c
	gcc build/target.c -c

compile_grammar: grammar.y libs/terminal_colors.h
	gcc y.tab.c -c

lexer:
	flex lexer.l
	gcc lex.yy.c -c

preprocessor: preprocessor/preprocessor.h preprocessor/preprocessor.c
	gcc preprocessor/preprocessor.c -c

libs: libs/file_table.c libs/file_table.h libs/symbol_table.o libs/arg_table.c libs/arg_table.h
	gcc libs/file_table.c -c
	gcc libs/symbol_table.c -c
	gcc libs/arg_table.c -c


main: main.c libs/terminal_colors.h libs/file_table.o libs/file_table.c libs/symbol_table.o libs/symbol_table.c internals.o target.o preprocessor.o
	gcc main.c lex.yy.o y.tab.o libs/file_table.o libs/symbol_table.o internals.o internals_backend.o arg_table.o target.o preprocessor.o -g -o dasm

clean:
	rm *.o
	rm *.tab.c
	#rm *.yy.
ifneq (,$(wildcard dasm))
	rm dasm
endif
ifneq (,$(wildcard build/))
	rm -r build
endif
	@$(MAKE) clean -C backend/
