#include <stdio.h>
#include "inset.h"
#include "alu_ops.h"
#include "../libs/arg_table.h"
#include "../libs/bin_buffer.h"
#include "../internals.h"
#include "../internals_backend.h"
#include "d16i.h"


/*Argument templates*/
//ARG_TEMPLATE_NTYPES_NODE load_assisted_ntypes = {2, 1}; //Types allowed per argument
//ARG_TEMPLATE_TYPES_NODE load_assisted_types =  {{TYPE_HI, TYPE_LO}, {TYPE_DONT_CARE}}; //Types IDs

/*ALU Instructions*/
INS_NODE_TEMPLATE add = {.op = iADD, .name="add", .nargs = 3, .relative_args = {0, 0, 0}, .asm_func = &assemble_alu};
INS_NODE_TEMPLATE sub = {.op = iSUB, .name="sub", .nargs = 3, .relative_args = {0, 0, 0}, .asm_func = &assemble_alu};
INS_NODE_TEMPLATE and = {.op = iAND, .name="and", .nargs = 3, .relative_args = {0, 0, 0}, .asm_func = &assemble_alu};
INS_NODE_TEMPLATE xor = {.op = iXOR, .name="xor", .nargs = 3, .relative_args = {0, 0, 0}, .asm_func = &assemble_alu};
INS_NODE_TEMPLATE or = {.op = iOR, .name="or", .nargs = 3, .relative_args = {0, 0, 0}, .asm_func = &assemble_alu};
INS_NODE_TEMPLATE not = {.op = iNOT, .name="not", .nargs = 3, .relative_args = {0, 0, 0}, .asm_func = &assemble_alu};
INS_NODE_TEMPLATE shftl = {.op = iSHFTL, .name="shftl", .nargs = 3, .relative_args = {0, 0, 0}, .asm_func = &assemble_alu};
INS_NODE_TEMPLATE shftr = {.op = iSHFTR, .name="shftr", .nargs = 3, .relative_args = {0, 0, 0}, .asm_func = &assemble_alu};

/*LOAD IMMEDIATE*/
INS_NODE_TEMPLATE loadi = {.op =  0x00, .name="load", .nargs = 3, .relative_args = {0, 0, 0}, .asm_func = &assemble_loadi};

/*Example to override a definition*/
INS_NODE_TEMPLATE loadi_assisted = {.op =  0x01, .name="load", .nargs = 2, .relative_args = {0, 0}, .asm_func = &assemble_loadi, .types = (int [][8]){{TYPE_HI, TYPE_LO}, {TYPE_DONT_CARE}}, .ntypes = (int[]){2,1}};





void assemble_loadi(BIN_BUFFER* bin_buffer, ARG_TABLE* arg_table, int op)
{
        switch (op)
        {
            case 0:
                printf("\t\t\t\tload immediate detected\n");
			    printf("\t\t\t\tADDR: ENCODED: %x\n", ENCODE_LI(arg_table->data[0].value, arg_table->data[1].value, arg_table->data[2].value, arg_table->data[2].value));
    			printf("\t\t\t\tARG 0: %d\n", arg_table->data[0].value);
    			printf("\t\t\t\tARG 1: %d\n", arg_table->data[1].value);
    			printf("\t\t\t\tARG 2: %d\n", arg_table->data[2].value);
    			printf("\t\t\t\tARG 3: %d\n", arg_table->data[3].value);
            break;
            case 1:
                printf("\t\t\t\tload assisted detected\n");
			    printf("\t\t\t\tADDR: ENCODED: %x\n", ENCODE_LI(arg_table->data[0].value, arg_table->data[1].value, arg_table->data[2].value, arg_table->data[2].value));
    			printf("\t\t\t\tARG 0: %d\n", arg_table->data[0].value);
    			printf("\t\t\t\tARG 1: %d\n", arg_table->data[1].value);
    			printf("\t\t\t\tARG 2: %d\n", arg_table->data[2].value);
    			printf("\t\t\t\tARG 3: %d\n", arg_table->data[3].value);
			break;

            default:
            break;
        }
        /*The load assisted is a function that combines two loadi instructions*/
}

void assemble_alu(BIN_BUFFER* bin_buffer, ARG_TABLE* arg_table, int op)
{
    printf("\t\t\t\tADDR: ENCODED: %x\n", ENCODE_ALUF(op, arg_table->data[0].value, arg_table->data[1].value, arg_table->data[2].value));
    printf("\t\t\t\tARG 0: %d\n", arg_table->data[0].value);
    printf("\t\t\t\tARG 1: %d\n", arg_table->data[1].value);
    printf("\t\t\t\tARG 2: %d\n", arg_table->data[2].value);
}