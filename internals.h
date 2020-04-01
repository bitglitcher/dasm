#pragma once

#ifndef INTERNALS
#define INTERNALS

#include <string.h>
#include <stdlib.h>
#include "libs/arg_table.h"
#include "libs/bin_buffer.h"
#include "libs/symbol_table.h"
#include "y.tab.h"


extern char* keywords [];
extern int keyword_id [];

typedef struct
{
    int op; //Instruction op
    char* name; //Name to match
    int nargs; //Number of arguments
    int* relative_args; //array of 0 or 1 to set relative arguments
    void (*asm_func)(BIN_BUFFER* bin_buffer, ARG_TABLE* arg_table, int op); //Function pointer to assembler function 
} INS_NODE_TEMPLATE;

typedef struct
{
    int op;
    ARG_TABLE args;
} INS_NODE;

//number handdling
void set_values(int);

int return_token(char* identifier);

/*16bit HI LO */
#define BYTE_LO(Data) (Data & 0xff)
#define BYTE_HI(Data) ((Data >> 8) & 0xff)

//Identifier stuff

extern char* identifiers [2];
extern int identifier_index;

#define IDENTIFIER_0 identifiers [0] 
#define IDENTIFIER_1 identifiers [1]
#define IDENTIFIER_2 identifiers [2]

void set_identifier(char* identifier_name);
void reset_identifiers();

#endif