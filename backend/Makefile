CC=gcc
FLAGS=


all:
	bison -d grammar.y --report=all
	flex lexer.l
	$(CC) $(FLAGS) lex.yy.c grammar.tab.c symbol_table.c backend_parser.c -g

clean:
	rm grammar.tab.c
	rm grammar.tab.h
	rm lex.yy.c
	rm grammar.output
	rm a.out
	rm target.*

run:
	./a.out < d32i.id

#Test the output files
test: target.h target.c
	gcc target.h -c
	gcc target.c -c

