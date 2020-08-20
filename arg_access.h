/*
 * Autor: Benjamin Herrera Navarro
 * 8/10/2020 7:12 AM
 * This file provides helper macros for better access of argument nodes
 */


#define GET_OP1 arg_table->data[0]
#define GET_OP2 arg_table->data[1]
#define GET_OP3 arg_table->data[2]
#define GET_OP4 arg_table->data[3]
#define GET_OP5 arg_table->data[4]

#define GET_OP1_VAL arg_table->data[0].value
#define GET_OP2_VAL arg_table->data[1].value
#define GET_OP3_VAL arg_table->data[2].value
#define GET_OP4_VAL arg_table->data[3].value
#define GET_OP5_VAL arg_table->data[4].value

#define GET_OP1_NAME arg_table->data[0].name
#define GET_OP2_NAME arg_table->data[1].name
#define GET_OP3_NAME arg_table->data[2].name
#define GET_OP4_NAME arg_table->data[3].name
#define GET_OP5_NAME arg_table->data[4].name

#define GET_OP1_NAME arg_table->data[0].domain
#define GET_OP2_NAME arg_table->data[1].domain
#define GET_OP3_NAME arg_table->data[2].domain
#define GET_OP4_NAME arg_table->data[3].domain
#define GET_OP5_NAME arg_table->data[4].domain

#define REGISTER "register"
#define NUMERIC "numeric"
#define ADDRESS "address"
