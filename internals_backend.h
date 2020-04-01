#pragma once
#ifndef INTERNALS_BACKEND
#define INTERNALS_BACKEND

#include "internals.h"
#include "arch/d16i.h"


/*regiter defenitions*/
extern char* regs [];
extern int reg_addr [];


//Instruction template array
extern INS_NODE_TEMPLATE* instructions [];


void assemble_ins(char* name, ARG_TABLE* arg_table);

#endif