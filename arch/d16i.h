#pragma once

#ifndef ARCH
#define ARCH

#include "../internals.h"
#include "inset.h"
#include "../libs/bin_buffer.h"

/*Instruction encoding*/

#define ENCODE_NOOP 0x0000
#define ENCODE_LI(hl, gs, rt, imm) ((0x01) | (hl << 3) | (gs << 4) | (rt << 5) | (imm << 8))
#define ENCODE_LSINS(ls, gs1, gs2, t1, p1) ((0x02) | (ls << 3) | (gs1 << 4) | (gs2 << 5) | (t1 << 6) | (p1 << 9))
#define ENCODE_ALUF(op, rt, s1, s2) (unsigned short)((0x03) | (op << 3) | (rt << 7) | (s1 << 10) | (s2 << 13))
#define ENCODE_INMI(op, imm) ((0x04) | (op << 3) | (ivr << 8))
#define ENCODE_JMPR(ivr, op, ap, t1, t2) ((0x05) | (ivr << 3) | (op << 4) | (ap << 7) | (t1 << 10) | (t2 << 13))
#define ENCODE_MOVF(hl_t, hl_s, ft, op, rt, s1) ((0x06) | (hl_t << 3) | (hl_s << 4) | (ft << 5) | (op << 6) | (rt << 10) | (s1 << 13))
#define ENCODE_JMPFR(ivr, op, ap, t1, t2) ((0x07) | (ivr << 3) | (op << 4) | (ap << 7) | (t1 << 10) | (t2 << 13))


#define REGS_NAMES \
    /*GPRS*/ \
    {"ax", "bx", "cx", "dx",\
     "ex", "fx", "gx", "hx",\
     "sp", "bp", "irqid"}

#define REGS_ADDRS \
    {0, 1, 2, 3,\
     4, 5, 6, 7,\
     0, 1, 2}

//including addr 0 because the backend subtracts 1 to the value
#define NREGS 11

/*Function prototypes must, have sometype of contex on runtime*/
/*op and name to give context, ARG_TABLE to assemble and bin buffer*/
void assemble_alu(BIN_BUFFER* bin_buffer, ARG_TABLE* arg_table, int op);


//ALU operations
extern INS_NODE_TEMPLATE add;
extern INS_NODE_TEMPLATE sub;
extern INS_NODE_TEMPLATE and;
extern INS_NODE_TEMPLATE xor;
extern INS_NODE_TEMPLATE or;
extern INS_NODE_TEMPLATE not;
extern INS_NODE_TEMPLATE shftl;
extern INS_NODE_TEMPLATE shftr;



#define INS_TEMPLATE_ARRAY \
    {          \
        &add,  \
        &sub,  \
        &and,  \
        &xor,  \
        &or,   \
        &not,  \
        &shftl,\
        &shftr,\
    }

#define N_INS_TEMPLATES 8

void assembler_func();

#define ASSMBLER_FUNCTION(INS) assembler_func(INS)

#endif