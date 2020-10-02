#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libs/arg_table.h"
#include "libs/bin_buffer.h"
#include "libs/symbol_table.h"
#include "y.tab.h"
//#include "arch/"

char* keywords [] = {"def", "alloc", "struct", "byte"};
int keyword_id [] = {DEF, ALLOC, STRUCT, BYTE}; //defined in the y.tab.h header file

//SYMBOL_TABLE local_table; //for identifiers

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

void init_internals()
{
    //init_symbol_table(&local_table);
}

int return_token(char* identifier)
{
    //printf("sizeof %d\n", sizeof((char*)keywords));
    for(int i = 0;i <= 3;i++)
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
    set_identifier(strdup(identifier));
    return IDENTIFIER;
}
