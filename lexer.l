%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
#include "arch/alu_ops.h"
#include "internals.h"


char* identifier_name;
int op_addr;


%}
%option nounput yylineno
%option noyywrap

STRING_P L?\"(\\.|[^\\"])*\"
IDENTIFIER ^[a-zA-Z_][a-zA-Z0-9_]*

%%
    

IDENTIFIER          {printf("IDENTIFIER\n"); return IDENTIFIER;};

"add"               {op_addr = op_type_add	; return OPERATION;};
"sub"               {op_addr = op_type_sub	; return OPERATION;};
"and"               {op_addr = op_type_and	; return OPERATION;};
"xor"               {op_addr = op_type_xor	; return OPERATION;};
"or"                {op_addr = op_type_or	; return OPERATION;};
"not"				{op_addr = op_type_not	; return OPERATION;};
"shftl"				{op_addr = op_type_shftl; return OPERATION;};
"shftr"				{op_addr = op_type_shftr; return OPERATION;};

"def"               return DEFINE;

"load"              return INS;
"store"             return INS;
"mov"               return INS;


[0-9]               {return NUMBER;}
[A-Fa-f0-9]         {return NUMBER;}

[ \r\n]             ;
.                   ;
[ \t]+              ;
%%
