/*
Autor: Benjamin Herrera Navarro
Recusive decent parser for the Dasm assembler
*/

/*Setup for lex*/
#define PARSER  yylex()
extern PARSER

typedef enum {IDENTIFIER, ,} tokens;

int expect(tokens token)
{
    if(token == yylex()) return 1;
}

int accept(tokens token)
{
    if(token == yylex()) return 1;
}

void parse_string(char* buffer)
{

}
void parse_buffer(char* buffer, int size)
{
    /*Expext An identifier then an instruction*/
}

void entry()
{

}
