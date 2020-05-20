/*
Written by: Benjamin Herrera Navarro
Backend interface lenguage
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

SYMBOL_TABLE symbol_table;

extern void reset_identifiers();
extern void yyparse();
extern void print_symbol_table();

#define default_output target

void gen_keywords()
{

}

void gen_arg_template()
{

}


void gen_ins()
{

}


void gen_memonics()
{

}


int main(void)
{
    init_symbol_table(&symbol_table);
    reset_identifiers();
    yyparse();
    print_symbol_table(&symbol_table);

    return 0;
}

