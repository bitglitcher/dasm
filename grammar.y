%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "internals_backend.h"
#include "libs/arg_table.h"
#include "internals.h"
//extern void init_arg_table(ARG_TABLE* arg_table); 

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

ARG_TABLE arg;

extern char* yytext;
extern int yylineno;
extern int yylex();
void yyerror(const char *str)
{
        fprintf(stderr,"error: on line %d, %s before token: %s\n",yylineno ,str, yytext);
}

extern char* identifier_name;

%}


%token OPERATION SEMICOLON DEF ALLOC IDENTIFIER INS NUMBER

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

arguments:
    IDENTIFIER
    {
        append_arg(&arg, match_args(yytext));
        printf("arguments detected: name: %s \t value %d\n", yytext, match_args(yytext));
    }
    |
    arguments ',' IDENTIFIER 
    {
        printf("arguments detected: name: %s \t value %d\n", yytext, match_args(yytext));
        append_arg(&arg, match_args(yytext));
    }
    ;

instruction:
    IDENTIFIER
    {
        printf("Instructions %s\n", IDENTIFIER_0);
        init_arg_table(&arg);
    } arguments ';'
    {
        assemble_ins(IDENTIFIER_0, &arg);
        reset_identifiers();
    }
    ;

defenition_exp:
    instruction
    |
    label
    |
    defenition_exp instruction
    |
    defenition_exp label
    ;
    
defenition:
    DEF '{' defenition_exp '}'
    {
        printf("DEF\n");
    }
    ;
label:
    IDENTIFIER ':'
    {
        printf("label\n");
    }
    ;

%%
