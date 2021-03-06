#pragma once
#ifndef INTERNALS_BACKEND
#define INTERNALS_BACKEND

#include "internals.h"



/*regiter defenitions*/
extern char* regs [];
extern int reg_addr [];

/*Target Specific Keyword array*/

extern char* target_keywords [];
extern int target_keywords_vals [];

//Instruction template array
extern INS_NODE_TEMPLATE* instructions [];


void assemble_ins(char* name, ARG_TABLE* arg_table);

ARG_NODE_TEMPLATE match_args(char* name);

void increment_addr();

int addr;

extern BIN_BUFFER bin_buffer;

#endif
