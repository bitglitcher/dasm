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

void yyerror(const char *str)
{
        fprintf(stderr,"error: on line %d, %s before token: %s\n",yylineno ,str, yytext);
}

extern SYMBOL_TABLE symbol_table;

char* domain;
char* linkof;
int scope_type;
extern void reset_identifiers();


//table to which link attributes
LIST* link_list;

%}

%union
{
	int val;
	char* id;
}
%type def
%type arg
%type macros
%token <id> IDENTIFIER
%token <val> NUMBER
%token <id> STRING

%token DEF ARG ENCODE MAX ARG_TEMPLATE MNEMONIC MACROS


%%

commands: %empty
    | commands command
    ;

command:
	def
	|
	arg
    |
    macros
    ;

identifiers:
	IDENTIFIER
	{
		//Store entry on symbol table
		append_symbol_with_list(&symbol_table, $1, TYPE_IDENTIFIER, 0, domain, scope_type, link_list);
		linkof = $1;
	}
	|
	identifiers ',' IDENTIFIER
	{
		//Store entry on symbol table
		append_symbol_with_list(&symbol_table, $3, TYPE_IDENTIFIER, 0, domain, scope_type, link_list);
		linkof = $3;
	}
	;
	
template_def_permissive:
	IDENTIFIER
	{
		//Append identifier name
		symbol_table.wait_slot = false;
		append_to_list(link_list, 0, $1, TYPE_IDENTIFIER);
	}
	|
	NUMBER
	{
		append_to_list(link_list, $1, NULL, TYPE_NUMBER);
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
		domain = strdup($2);
		append_symbol(&symbol_table, domain, TYPE_ARG, 0, "none", TYPE_ARG);
		//Set domain so template_defsdomain its data in the required domain
		scope_type = TYPE_ARG;
	} '{' template_defs '}' {link_list = NULL;}
	;

arg_template:
	ARG_TEMPLATE '{'  {link_list = create_list(); scope_type = TYPE_ARG_TEMPLATE;} template_defs '}' {link_list = NULL;}
	;

mnemonic:
	MNEMONIC '{' {scope_type = TYPE_MNEMONIC;} STRING '}'
	{
		append_symbol(&symbol_table, $4, TYPE_MNEMONIC, 0, domain, TYPE_MNEMONIC);
	}
	;

max:
	MAX '{' {link_list = create_list(); scope_type = TYPE_MAX;} template_defs '}' {link_list = NULL;}
	;

encode:
	ENCODE '{' {scope_type = TYPE_ENCODE;} STRING '}'
	{
	    append_symbol(&symbol_table, $4, TYPE_ENCODE, 0, domain, TYPE_ENCODE);
	}
	;

def_branch:
	mnemonic
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
			append_symbol(&symbol_table, $2, TYPE_DEF, 0, "none", TYPE_DEF);
			domain = $2;
		}
		'{' recusive_def_branch '}'
	;

macros:
    MACROS '{' STRING '}'
    {
        printf("\t\t\tMACRO DETECTED\n");
        append_symbol(&symbol_table, $3, TYPE_MACRO, 0, "none", TYPE_MACRO);
        link_list = NULL;
        scope_type = TYPE_MACRO;
    }
    ;
%%
