%{
#include <stdio.h>
#include <stdlib.h>

#include "y.tab.h"


char* identifiers [4];
int identifier_index = 0;



void set_identifier(char* identifier_name)
{
    identifiers [identifier_index] = strdup(identifier_name);
    identifier_index++;
}

void reset_identifiers()
{
    identifier_index = 0;
}

char * keywords [] = {"arg", "encode", "assemble", "max", "def", "arg_template"};
int keyword_id [10] = {ARG, ENCODE, ASSEMBLE, MAX, DEF, ARG_TEMPLATE};
int return_token(char* identifier)
{
    //printf("sizeof %d\n", sizeof((char*)keywords));
    for(int i = 0;i <= 5;i++)
    {
        //printf("To compare %s\n", identifier);
        if(strcmp(keywords [i], identifier) == 0)
        {
            if(DEF == keyword_id [i])
            {
                //printf("DEF returned\n");
            }
            return keyword_id [i]; 
        }
    }
    //if nothing
    printf("identifier detected %s\n", identifier);
    return IDENTIFIER;
}


int val;

%}

%option nounput yylineno
%option noyywrap



%%

[a-zA-Z_][a-zA-Z0-9_]*      {set_identifier(strdup(yytext));printf("IDENTIFIER\n"); return return_token(yytext);};

(0x)+[A-Fa-f0-9]*	        {val=strtol(yytext,NULL,0); return NUMBER;}
[0-9]*			            {val=atoi(yytext); return NUMBER;}
(0b)+[0-1]*		            {val=strtol(yytext,NULL,2); return NUMBER;}


"}"			                return '}';
"{"			                return '{';
"("			                return '(';
")"			                return ')';
","                         return ',';

[ \r\n]                     ;
.                           ;
[ \t]+                      ;

%%

int main(void)
{
   yyparse();
   return 0;
}
