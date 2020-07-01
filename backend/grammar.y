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
extern char* string_literal;

void yyerror(const char *str)
{
        fprintf(stderr,"error: on line %d, %s before token: %s\n",yylineno ,str, yytext);
}

extern char* identifiers [4];
extern SYMBOL_TABLE symbol_table;

char* domain;
char* linkof;
int scope_type;
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
		append_symbol_with_list(&symbol_table, identifiers[0], TYPE_IDENTIFIER, 0, domain, scope_type, link_list);
		linkof = strdup(identifiers[0]);
		reset_identifiers();
	}
	|
	identifiers ',' IDENTIFIER
	{
		//Store entry on symbol table
		append_symbol_with_list(&symbol_table, identifiers[0], TYPE_IDENTIFIER, 0, domain, scope_type, link_list);
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
		domain = strdup(identifiers[0]);
		append_symbol(&symbol_table, domain, TYPE_ARG, 0, "none", TYPE_ARG);
		//Set domain so template_defsdomain its data in the required domain
		scope_type = TYPE_ARG;
	} '{' template_defs '}' {link_list = NULL;}
	;

arg_template:
	ARG_TEMPLATE '{'  {link_list = create_list(); scope_type = TYPE_ARG_TEMPLATE;} template_defs '}' {link_list = NULL;}
	;

assemble:
	ASSEMBLE '{' {scope_type = TYPE_ASSEMBLE;} STRING '}'
	{
		append_symbol(&symbol_table, string_literal, TYPE_ASSEMBLE, 0, domain, TYPE_ASSEMBLE);
	}
	;

max:
	MAX '{' {link_list = create_list(); scope_type = TYPE_MAX;} template_defs '}' {link_list = NULL;}
	;

encode:
	ENCODE '{' {scope_type = TYPE_ENCODE;} STRING '}'
	{
	    append_symbol(&symbol_table, string_literal, TYPE_ENCODE, 0, domain, TYPE_ENCODE);
	}
	;

def_branch:
	assemble
	|
	arg_template
	|
	max
	|
	encode
	|
	%empty
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
			append_symbol(&symbol_table, identifiers [0], TYPE_DEF, 0, "none", TYPE_DEF);
			domain = identifiers[0];
			reset_identifiers();
		}
		'{' recusive_def_branch '}'
	;

%%
