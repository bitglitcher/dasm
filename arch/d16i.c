#include <stdio.h>
//#include "d16i.h"
#include "alu_ops.h"
#include "../libs/arg_table.h"
#include "../libs/bin_buffer.h"
#include "../internals.h"
#include "../internals_backend.h"
#include "d16i.h"


INS_NODE_TEMPLATE add = {.op = 0x00, .name="add", .nargs = 3, .relative_args = {0, 0, 0}, .asm_func = &assemble_alu};
INS_NODE_TEMPLATE sub = {.op = 0x01, .name="sub", .nargs = 3, .relative_args = {0, 0, 0}, .asm_func = &assemble_alu};
INS_NODE_TEMPLATE and = {.op = 0x02, .name="and", .nargs = 3, .relative_args = {0, 0, 0}, .asm_func = &assemble_alu};
INS_NODE_TEMPLATE xor = {.op = 0x03, .name="xor", .nargs = 3, .relative_args = {0, 0, 0}, .asm_func = &assemble_alu};
INS_NODE_TEMPLATE or = {.op = 0x04, .name="or", .nargs = 3, .relative_args = {0, 0, 0}, .asm_func = &assemble_alu};
INS_NODE_TEMPLATE not = {.op = 0x05, .name="not", .nargs = 3, .relative_args = {0, 0, 0}, .asm_func = &assemble_alu};
INS_NODE_TEMPLATE shftl = {.op = 0x06, .name="shftl", .nargs = 3, .relative_args = {0, 0, 0}, .asm_func = &assemble_alu};
INS_NODE_TEMPLATE shftr = {.op = 0x07, .name="shftr", .nargs = 3, .relative_args = {0, 0, 0}, .asm_func = &assemble_alu};




void assemble_alu(BIN_BUFFER* bin_buffer, ARG_TABLE* arg_table, int op)
{
        printf("\t\t\t\tADDR: ENCODED: %x\n", ENCODE_ALUF(op, arg_table->data[0].value, arg_table->data[1].value, arg_table->data[2].value));
        printf("\t\t\t\tARG 0: %d\n", arg_table->data[0].value);
        printf("\t\t\t\tARG 1: %d\n", arg_table->data[1].value);
        printf("\t\t\t\tARG 2: %d\n", arg_table->data[2].value);
    /*switch (op)
    {
    case op_type_add:
        //append_byte(bin_buffer, match_args())
    break;
    case op_type_sub:

    break;
    case op_type_and:

    break;
    case op_type_xor:

    break;
    case op_type_or:

    break;
    case op_type_not:

    break;
    case op_type_shftl:

    break;
    case op_type_shftr:

    break;
    default:
        break;
    }*/
}