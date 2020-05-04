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
extern int val;


void yyerror(const char *str)
{
        fprintf(stderr,"error: on line %d, %s before token: %s\n",yylineno ,str, yytext);
}

extern char* identifier_name;

%}


%token DEF IDENTIFIER ARG ENCODE MAX ARG_TEMPLATE ASSEMBLE NUMBER STRING

%%
commands: /* empty */
    | commands command
    ;

command:
	def
    |
	arg
    ;

identifiers:
	IDENTIFIER
	|
	identifiers ',' IDENTIFIER
	;

template_def_permissive:
	identifiers
	|
	NUMBER
	;

template_def_permissives:
	template_def_permissive
	|
	template_def_permissives ',' template_def_permissive
	;
	
template_def:
	'(' identifiers ')' '{' template_def_permissives '}'
	;

template_defs:
	template_defs
	|
	template_defs ',' template_def
	;

arg:
	ARG IDENTIFIER '{' template_defs '}'
	;

arg_template:
	ARG_TEMPLATE '{' template_defs '}'
	;

max:
	MAX '{' template_defs '}'
	;

encode:
	ENCODE '{' template_defs '}'
	;

assemble:
	ASSEMBLE '{' STRING '}'
	;

def_branch:
	arg
	;

def:
   DEF IDENTIFIER '{' def_branch '}'
	;




