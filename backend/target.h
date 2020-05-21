#ifndef _TARGET_
#define _TARGET_

#include "../internals.h"



/*----------------KEYWORDS----------------*/
char* taget_keywords = {"ax", "cx", "lo", "hi"};




INS_NODE_TEMPLATE load_assisted = {.op = iSHFTR, .name="load_assisted", .nargs = 3, .relative_args = {0, 0, 0}, .asm_func = &assemble_alu};
INS_NODE_TEMPLATE load = {.op = iSHFTR, .name="load", .nargs = 3, .relative_args = {0, 0, 0}, .asm_func = &assemble_alu};
INS_NODE_TEMPLATE store = {.op = iSHFTR, .name="store", .nargs = 3, .relative_args = {0, 0, 0}, .asm_func = &assemble_alu};
INS_NODE_TEMPLATE add = {.op = iSHFTR, .name="add", .nargs = 3, .relative_args = {0, 0, 0}, .asm_func = &assemble_alu};
INS_NODE_TEMPLATE sub = {.op = iSHFTR, .name="sub", .nargs = 3, .relative_args = {0, 0, 0}, .asm_func = &assemble_alu};




#endif