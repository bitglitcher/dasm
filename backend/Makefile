CC=gcc
FLAGS=

all: grammar.y lexer.l ../preprocessor/preprocessor.c backend_parser.c
	bison -d grammar.y --report=all
	flex lexer.l
	$(CC) $(FLAGS) lex.yy.c grammar.tab.c symbol_table.c ../preprocessor/preprocessor.c backend_parser.c -g -o backend_gen

clean:
	rm grammar.tab.c
	rm grammar.tab.h
	rm lex.yy.c
	rm grammar.output
	rm backend_gen
	#rm target.*

run:
	./backend_gen d32i.id

#Test the output files
test: target.h target.c
	gcc target.h -c
	gcc target.c -c
