/*
Autor: Benjamin Herrera Navarro
6:20AM Implementando una gramatica simple, como prueba del assembler
*/

#include <argp.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "libs/terminal_colors.h"
#include "libs/file_table.h"
#include "libs/symbol_table.h"
#include "internals.h"

const char *argp_program_version = "dasm rebuilt";
const char *argp_program_bug_address = "<draketaco@github.com>";
static char doc[] = "Simple Assembler for the D series architecture.";
static char args_doc[] = "[FILENAME]...";

static struct argp_option options[] = { 
    { "output", 'o', "FILE", 0, "Place output file as <file>."},
    { "table", 't', 0, 0, "Display symbol table."},
    { 0 } 
};

struct arguments {
    char* output_file;
    char* input_file;
    bool table_display;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;
    switch (key) {
    case 'o': arguments->output_file = strdup(arg); break;
    case 't': arguments->table_display = true; break;
    case ARGP_KEY_ARG: arguments->input_file = strdup(arg); return 0;
    default: return ARGP_ERR_UNKNOWN;
    }   
    return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc, 0, 0, 0 };


//Lex and Bison Stuff
extern int yyparse();
extern int yy_scan_bytes ( const char *, int);
extern int yylex();

extern void init_internals();
//FILE TABLE
FILE_TABLE file_table;
SYMBOL_TABLE symbol_table;

//Parsing variables
bool dry_run = true;

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
        printf("\tname %s\n", symbol_table->data[i].name);
        printf("\ttype %d\n", symbol_table->data[i].type);
    }
}

int main(int argc, char *argv[])
{
    struct arguments arguments;
    arguments.output_file = NULL;
    arguments.input_file = NULL;
    arguments.table_display = false;

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    if(arguments.input_file != NULL)
    {
        printf("Input File %s\n", arguments.input_file);
        if(arguments.output_file == NULL)
        {
            printf("Using default output -> ROM.bin\n");
            arguments.output_file = "rom.bin";
        }
        else
        {
            printf("Using specified output -> %s\n", arguments.output_file);
        }
        printf("\n\n\nOpening file: %s\n", arguments.output_file);
        //File table
        init_file_table(&file_table);
        init_symbol_table(&symbol_table);
        init_internals();
        append_file(&file_table, arguments.input_file);
        //Parse first file
        printf("Scanning File\n");
        FILE_NODE* file_node = search_file(&file_table, arguments.input_file);
        if(file_node)
        {
            dry_run = true;
            yy_scan_bytes(file_node->data, file_node->size);
            yyparse();
            //yypop_buffer_state();
            //yyfree();
            dry_run = false;
            yy_scan_bytes(file_node->data, file_node->size);
            yyparse();
            if(arguments.table_display) print_symbol_table(&symbol_table);
        }
        else
        {
            printf("dasm: " ANSI_COLOR_RED "fatal error" ANSI_COLOR_RESET ": empty file_node\n");
        }
        
    }
    else
    {
        printf("dasm: " ANSI_COLOR_RED "fatal error" ANSI_COLOR_RESET ": no input file\n");
    }

    //FILE* main_file;
    //fopen(main_file, )
}
