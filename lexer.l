%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
#include "internals.h"

//extern int return_token(char* identifier);


char* identifier_name;
int op_addr;
int val;
//IDENTIFIER ^[a-zA-Z_][a-zA-Z0-9_]*
//"add"               {op_addr = op_type_add	; return OPERATION;};
//"sub"               {op_addr = op_type_sub	; return OPERATION;};
//"and"               {op_addr = op_type_and	; return OPERATION;};
//"xor"               {op_addr = op_type_xor	; return OPERATION;};
//"or"                {op_addr = op_type_or	; return OPERATION;};
//"not"				{op_addr = op_type_not	; return OPERATION;};
//"shftl"				{op_addr = op_type_shftl; return OPERATION;};
//"shftr"				{op_addr = op_type_shftr; return OPERATION;};
//"load"              return INS;
//"store"             return INS;
//"mov"               return INS;


//append_symbol(&local_table, yytext, 0x00, "none");

%}
%option nounput yylineno
%option noyywrap

STRING_P L?\"(\\.|[^\\"])*\"
IDENTIFIER [A-Za-z0-9]*

%%
    

[a-zA-Z_][a-zA-Z0-9_]*      {set_identifier(strdup(yytext));printf("IDENTIFIER %s\n", yytext); return return_token(yytext);};

(0-9)*                      {val=atoi(yytext); return NUMBER;}
(0x)+[A-Fa-f0-9]*           {val=strtol(yytext,NULL,0); return NUMBER;}

":"                         return ':';
"("                         return '(';
")"                         return ')';
","                         return ',';
";"                         return ';';
"{"                         return '{';
"}"                         return '}';

[ \r\n]                     ;
.                           ;
[ \t]+                      ;

%%
