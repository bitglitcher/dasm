/*
Written by: Benjamin Herrera Navarro
Backend interface lenguage
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"
#include "backend_parser_types.h"

SYMBOL_TABLE symbol_table;

extern void reset_identifiers();
extern void yyparse();
extern void print_symbol_table();

#define default_output "target.h"

#define PROLOGUE \
    "#ifndef _TARGET_\n#define _TARGET_\n\n#include \"../internals.h\"\n\n\n\n"

#define EPILOUGE "\n\n\n\n#endif"

/* all tree gen functions will append data to the buffer argument*/
void gen_keywords(SYMBOL_TABLE* symbol_table, FILE* file)
{
    bool first = true;
    //all nodes within the scope_type of arg are keywords
    printf("----------------ARG DOMAINS----------------\n");
    //extract and print all arg domains
    if(symbol_table)
    {
        fputs("/*----------------KEYWORDS----------------*/\n", file);
        fputs("char* taget_keywords = {", file);
        for(int i = 0;i <= symbol_table->size;i++)
        {
            if(symbol_table->data + i)
            {
                if(symbol_table->data[i].scope_type == TYPE_ARG & symbol_table->data[i].type == TYPE_IDENTIFIER)
                {
                    if(first)
                    {
                        first = false;
                    }
                    else
                    {
                        fputs(", ", file);
                    }
                    
                    printf("keyword found -> %s\n", symbol_table->data[i].name);
                    //check is there is another element after this one
                    fprintf(file, "\"%s\"", symbol_table->data[i].name);
                }
            }
        }
        fputs("};\n", file);
        fputs("\n\n\n\n", file);
    }
}

void gen_arg_template(SYMBOL_TABLE* symbol_table, char* buffer)
{
    //all nodes within the scope_type of arg_template are templates
    printf("----------------ARG TEMPLATES----------------\n");
    //extract and print all the arg template domains 
    if(symbol_table)
    {
        for(int i = 0;i <= symbol_table->size;i++)
        {
            if(symbol_table->data + i)
            {
                if(symbol_table->data[i].scope_type == TYPE_ARG & symbol_table->data[i].type == TYPE_IDENTIFIER)
                {
                    printf("keyword found -> %s\n", symbol_table->data[i].name);
                }
            }
        }
    }
}


void gen_ins(SYMBOL_TABLE* symbol_table, FILE* file)
{
   //all nodes within the scope_type of arg_template are templates
    printf("----------------INSTRUCTIONS----------------\n");
    //extract and print all the arg template domains 
    if(symbol_table)
    {
        for(int i = 0;i <= symbol_table->size;i++)
        {
            if(symbol_table->data + i)
            {
                if(symbol_table->data[i].scope_type == TYPE_DEF)
                {
                    printf("instruction found -> %s\n", symbol_table->data[i].name);
                    //INS_NODE_TEMPLATE shftr = {.op = iSHFTR, .name="shftr", .nargs = 3, .relative_args = {0, 0, 0}, .asm_func = &assemble_alu};
                    fprintf(file, "INS_NODE_TEMPLATE %s = {.op = iSHFTR, .name=\"%s\", .nargs = 3, .relative_args = {0, 0, 0}, .asm_func = &assemble_alu};\n", \
                        symbol_table->data[i].name, symbol_table->data[i].name);
                }
            }
        }

    }
}


void gen_memonics(SYMBOL_TABLE* symbol_table, char* buffer)
{

}

FILE*  output_file;

int main(void)
{
    output_file = fopen (default_output,"w");

    init_symbol_table(&symbol_table);
    reset_identifiers();
    yyparse();
    print_symbol_table(&symbol_table);

    fputs(EPILOUGE, output_file);

    gen_keywords(&symbol_table, output_file);
    gen_ins(&symbol_table, output_file);

    fputs(PROLOUGE, output_file);
    
    if (output_file!=NULL)
    {
      fclose (output_file);
    }
    return 0;
}

