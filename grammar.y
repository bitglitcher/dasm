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

ARG_TABLE* arg_table = NULL;

extern char* yytext;
extern int yylineno;
extern int yylex();
extern int val;


void yyerror(const char *str)
{
        fprintf(stderr,"error: on line %d, %s before token: %s\n",yylineno ,str, yytext);
}

extern char* identifier_name;

extern SYMBOL_TABLE symbol_table;

char* current_scope;

char* ins;

extern bool dry_run;

int struct_size_cnt;
%}

%union
{
    int val;
    char* id;
}
%token OPERATION SEMICOLON DEF ALLOC INS STRUCT BYTE
%token <val> NUMBER
%token <id> IDENTIFIER
%type <id> struct_type_def argument

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
    |
    struct
    ;

argument:
    IDENTIFIER '.' IDENTIFIER
    {
        if(!dry_run)
        {
            printf("struct access %s.%s\n", $3, $1);
            SYMBOL_NODE* symb_node = search_symbol(&symbol_table, $3, $1);
            if(symb_node)
            {
                ARG_NODE_TEMPLATE node;
                node.value = symb_node->addr;
                node.domain = "numeric";
                append_arg(arg_table, node);
            }
            else
            {
                printf("error: no %s.%s was found", $3, $1);
            }
        }
    }
    |
    IDENTIFIER
    {
        if(!dry_run)
        {
            append_arg(arg_table, match_args($1));
            printf("arguments detected: name: %s \t value %d\n", $1, match_args($1));
        }
    }
    |
    NUMBER
    {
        if(!dry_run)
        {
            printf("arguments number detected: %d\n", val);
            ARG_NODE_TEMPLATE node;
            node.value = val;
            node.domain = "numeric";
            append_arg(arg_table, node);
        }
    }
    |
    '[' NUMBER ']'
    {
        if(!dry_run)
        {
            printf("argument address detected\n", val);
            ARG_NODE_TEMPLATE node;
            node.value = val;
            node.domain = "address";
            append_arg(arg_table, node);
        }
    }
    ;

arguments:
    |
    argument
    |
    argument ',' arguments
    ;

instruction:
    IDENTIFIER
    {   
        if(!dry_run)
        {
            printf("Instructions %s\n", $1);
            arg_table = malloc(sizeof(ARG_TABLE));
            init_arg_table(arg_table);
        }
    } arguments ';'
    {
        if(!dry_run)
        {
            assemble_ins($1, arg_table);
            free(arg_table);
        }
        increment_addr();
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
        if(dry_run)
        {
            printf("label: %s\n", IDENTIFIER_0);
            append_symbol(&symbol_table, $1, TYPE_LABEL, addr, "none");
        }
    }
    ;

struct_type_def:
    BYTE NUMBER ',' IDENTIFIER ';'
    {
        if(dry_run)
        {
            append_symbol(&symbol_table, strdup($4), TYPE_STRUCT_MEMBER, struct_size_cnt, current_scope);
            struct_size_cnt += $2;
        }
    }
    ;

recursive_struct_types:
    |
    recursive_struct_types struct_type_def
    ;

struct:
    STRUCT IDENTIFIER '{' 
    {
        if(dry_run)
        {
            struct_size_cnt = 0;
            current_scope = $2;
            append_symbol(&symbol_table, $2, TYPE_STRUCT, 0x00, "struct");
        }
    } recursive_struct_types '}'
    ;

%%
