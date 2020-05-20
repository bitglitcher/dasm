%{
#include <stdio.h>
#include <stdlib.h>
#include "symbol_table.h"
#include "grammar.tab.h"


char* identifiers [4];
int identifier_index = 0;



void set_identifier(char* identifier_name)
{
    identifiers [identifier_index] = strdup(identifier_name);
    //identifier_index++;
    printf("identifier set %s \t\t index %d\n", identifier_name, identifier_index);
}

void reset_identifiers()
{
    identifier_index = 0;
}

char * keywords [] = {"arg", "encode", "assemble", "max", "def", "arg_template"};
int keyword_id [10] = {ARG, ENCODE, ASSEMBLE, MAX, DEF, ARG_TEMPLATE};

const char* scope_names [] = {"def", "arg", "assemble", "encode", "max", "arg_template"};

int return_token(char* identifier)
{
    //printf("sizeof %d\n", sizeof((char*)keywords));
    for(int i = 0;i <= 5;i++)
    {
        //printf("To compare %s\n", identifier);
        if(strcmp(keywords [i], identifier) == 0)
        {
            if(ARG == keyword_id [i])
            {
                //printf("ARG returned\n");
            }
            //printf("\treturned %s\n", keywords [i]);
            return keyword_id [i]; 
        }
    }
    //if nothing
    //printf("identifier detected %s\n", identifier);
    set_identifier(identifier);
    return IDENTIFIER;
}

/*set_identifier(strdup(yytext)); printf("IDENTIFIER %s\n", yytext);*/

int val;
char* string_literal;

void print_symbol_table(SYMBOL_TABLE* symbol_table)
{
    printf("\n\n------------SYMBOL_TABLE------------\n");
    printf("size: %d\n", symbol_table->size);
    printf("capacity: %d\n", symbol_table->capacity);
    printf("wait_slot: %d\n", symbol_table->wait_slot);
    for(int i = 0;i <= symbol_table->size;i++)
    {
        printf("NODE: 0x%x\n", i);
        printf("\taddr %d\n", symbol_table->data[i].addr);
        printf("\tdomain %s\n", symbol_table->data[i].domain);
        printf("\tscope_type %d -> %s\n", symbol_table->data[i].scope_type, scope_names [symbol_table->data[i].scope_type]);
        printf("\tname %s\n", symbol_table->data[i].name);
        printf("\ttype %d\n", symbol_table->data[i].type);
        printf("\tlist 0x%x\n", symbol_table->data[i].list);
        if(symbol_table->data[i].list)
        {
            for(int x = 0;x <= symbol_table->data[i].list->size;x++)
            {
                printf("\t\tcapacity %d\n", symbol_table->data[i].list->capacity);
                printf("\t\tsize %d\n", symbol_table->data[i].list->size);
                printf("\t\twait_slot %d\n", symbol_table->data[i].list->wait_slot);
                printf("\t\t\tval %d\n", symbol_table->data[i].list->data[x].val);
                printf("\t\t\tidentifier %s\n", symbol_table->data[i].list->data[x].identifier);
                printf("\t\t\ttype %d\n", symbol_table->data[i].list->data[x].type);

            }
        }
    }
}


%}

%option nounput yylineno
%option noyywrap


%%

[a-zA-Z_][a-zA-Z0-9_]*      return return_token(yytext);

(0x)+[A-Fa-f0-9]*	        {val=strtol(yytext,NULL,0); return NUMBER;}
[0-9]*			            {val=atoi(yytext); return NUMBER;}
(0b)+[0-1]*		            {val=strtol(yytext,NULL,2); return NUMBER;}

\"(\\.|[^"\\])*\"           {string_literal = strdup(yytext); return STRING;}

"}"			                return '}';
"{"			                return '{';
"("			                return '(';
")"			                return ')';
","                         return ',';
"%"                         return '%';

[ \r\n]                     ;
.                           ;
[ \t]+                      ;

%%

