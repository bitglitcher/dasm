#pragma once

#ifndef ARCH
#define ARCH

#include "../internals.h"
#include "inset.h"
#include "../libs/bin_buffer.h"

/*Instruction encoding*/

#define ENCODE_NOOP (unsigned short)0x0000
#define ENCODE_LI(hl, gs, rt, imm) (unsigned short)((0x01) | (hl << 3) | (gs << 4) | (rt << 5) | (imm << 8))
#define ENCODE_LSINS(ls, gs1, gs2, t1, p1) (unsigned short)((0x02) | (ls << 3) | (gs1 << 4) | (gs2 << 5) | (t1 << 6) | (p1 << 9))
#define ENCODE_ALUF(op, rt, s1, s2) (unsigned short)((0x03) | (op << 3) | (rt << 7) | (s1 << 10) | (s2 << 13))
#define ENCODE_INMI(op, imm) (unsigned short)((0x04) | (op << 3) | (ivr << 8))
#define ENCODE_JMPR(ivr, op, ap, t1, t2) (unsigned short)((0x05) | (ivr << 3) | (op << 4) | (ap << 7) | (t1 << 10) | (t2 << 13))
#define ENCODE_MOVF(hl_t, hl_s, ft, op, rt, s1) (unsigned short)((0x06) | (hl_t << 3) | (hl_s << 4) | (ft << 5) | (op << 6) | (rt << 10) | (s1 << 13))
#define ENCODE_JMPFR(ivr, op, ap, t1, t2) (unsigned short)((0x07) | (ivr << 3) | (op << 4) | (ap << 7) | (t1 << 10) | (t2 << 13))

/*Argument templates to be used in D16i.c intead of using explisit values*/
#define TYPE_HI 0x00
#define TYPE_LO 0x01


#define REGS_NAMES \
    /*GPRS*/ \
    {"ax", "bx", "cx", "dx",\
     "ex", "fx", "gx", "hx",\
     "sp", "bp", "irqid"}

#define REGS_ADDRS \
    {0, 1, 2, 3,\
     4, 5, 6, 7,\
     0, 1, 2}

/*To diferentiate different types of registers*/
#define REG_CLASSES \
    {0, 0, 0, 0,\
     0, 0, 0, 0,\
     1, 1, 1}

//including addr 0 because the backend subtracts 1 to the value
#define NREGS 11


#define TARGET_KEYWORDS \
    {"hi", "lo" \
    }

#define TARGET_KEYWORDS_VALS \
    {1, 0 \
    };

#define N_TARGET_KEYWORDS 2

#define TARGET_KEYWORDS_TYPES \
    {TYPE_HI, TYPE_LO}

/*Function prototypes must, have sometype of contex on runtime*/
/*op and name to give context, ARG_TABLE to assemble and bin buffer*/
void assemble_alu(BIN_BUFFER* bin_buffer, ARG_TABLE* arg_table, int op);
void assemble_loadi(BIN_BUFFER* bin_buffer, ARG_TABLE* arg_table, int op);

//ALU operations
extern INS_NODE_TEMPLATE add;
extern INS_NODE_TEMPLATE sub;
extern INS_NODE_TEMPLATE and;
extern INS_NODE_TEMPLATE xor;
extern INS_NODE_TEMPLATE or;
extern INS_NODE_TEMPLATE not;
extern INS_NODE_TEMPLATE shftl;
extern INS_NODE_TEMPLATE shftr;
extern INS_NODE_TEMPLATE loadi;
extern INS_NODE_TEMPLATE loadi_assisted;

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
        &loadi,\
        &loadi_assisted\
    }

#define N_INS_TEMPLATES 10

void assembler_func();

#define ASSMBLER_FUNCTION(INS) assembler_func(INS)

//Memory Addresses per instruction
#define NADDR_INS 1 

#endif