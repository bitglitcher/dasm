%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "symbol_table.h"
#include "backend_parser_types.h"

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

extern char* identifiers [4];
extern SYMBOL_TABLE symbol_table;

char* domain;
char* linkof;
extern void reset_identifiers();

//table to which link attributes
LIST* link_list;

%}

%token DEF IDENTIFIER ARG ENCODE MAX ARG_TEMPLATE ASSEMBLE NUMBER STRING


%%

commands: %empty
    | commands command
    ;

command:
	def
	|
	arg
    ;

identifiers:
	IDENTIFIER
	{
		//Store entry on symbol table
		append_symbol_with_list(&symbol_table, identifiers[0], TYPE_IDENTIFIER, 0, domain, link_list);
		linkof = strdup(identifiers[0]);
		reset_identifiers();
	}
	|
	identifiers ',' IDENTIFIER
	{
		//Store entry on symbol table
		append_symbol_with_list(&symbol_table, identifiers[0], TYPE_IDENTIFIER, 0, domain, link_list);
		linkof = strdup(identifiers[0]);
		reset_identifiers();
	}
	;
	
template_def_permissive:
	IDENTIFIER
	{
		//Append identifier name
		symbol_table.wait_slot = false;
		append_to_list(link_list, 0, identifiers[0], TYPE_IDENTIFIER);
		reset_identifiers();
	}
	|
	NUMBER
	{
		append_to_list(link_list, val, NULL, TYPE_NUMBER);
	}
	;

template_def_permissives:
	template_def_permissive
	|
	template_def_permissives ',' template_def_permissive
	;

template_def:
	%empty
	|
	'(' {link_list = create_list();} identifiers ')' '{' template_def_permissives '}' {link_list = NULL;}
	;

template_defs:
	template_def
	|
	template_defs ',' template_def
	;

arg:
	ARG IDENTIFIER
	{
		append_symbol(&symbol_table, identifiers [0], TYPE_ARG, 0, "none");
		//Set domain so template_defs stores its data in the required domain
		domain = strdup(identifiers [0]);
		reset_identifiers();
	} '{' template_defs '}'
	;

arg_template:
	ARG_TEMPLATE '{' template_defs '}'
	;

assemble:
	ASSEMBLE '{' STRING '}'
	;

max:
	MAX '{' template_defs '}'
	;

encode:
	ENCODE '{' STRING '}'
	;

def_branch:
	arg
	|
	assemble
	|
	arg_template
	|
	max
	|
	encode
	;

recusive_def_branch:
	def_branch
	|
	recusive_def_branch def_branch 
	;

def:
   	DEF IDENTIFIER 
	   	{
			//Create an enrty on the symbol table
			append_symbol(&symbol_table, identifiers [0], TYPE_DEF, 0, "none");
			reset_identifiers();
		}
		'{' recusive_def_branch '}'
	;

%%
