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


%token DEF IDENTIFIER ARG ENCODE MAX ARG_TEMPLATE ASSEMBLE NUMBER

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

arg_def_template_permissive:
	identifiers
	|
	NUMBER
	;

arg_def_template_permissives:
	arg_def_template_permissive
	|
	arg_def_template_permissives ',' arg_def_template_permissive

arg_template:
	'(' identifiers ')' '{' arg_def_template_permissives '}'
	;

arg_templates:
	arg_template
	|
	arg_templates ',' arg_template
	;

arg:
	ARG IDENTIFIER '{' arg_templates '}'
	;

def_branch:
	arg
	;

def:
   DEF IDENTIFIER '{'  '}'
	;




