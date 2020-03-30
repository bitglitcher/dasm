%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 

extern char* yytext;
extern int yylineno;
extern int yylex();
void yyerror(const char *str)
{
        fprintf(stderr,"error: on line %d, %s before token: %s\n",yylineno ,str, yytext);
}

%}


%token OPERATION SEMICOLON DEFINE IDENTIFIER INS NUMBER

%%
commands: /* empty */
    | commands command
    ;

command:
    instruction
    |
    defenition
    |
    label
    ;

instruction:
    OPERATION
    {
        printf("OPERATION!!!!!!!!!\n");
    }
    ;
defenition:
    DEFINE
    {
        printf("DEF\n");
    }
    ;
label:
    IDENTIFIER ':'
    {
        printf("label");
    }
    ;

%%
