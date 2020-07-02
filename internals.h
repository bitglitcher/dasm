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

/*Structs for the instruction maching*/
typedef struct
{
	int op; //Instruction op
	char* name; //Name to match
	int nargs;
	int *ntypes; //Number of permissive types per argument
	int *type;
	int n_templates;
	void (*asm_func)(BIN_BUFFER* bin_buffer, ARG_TABLE* arg_table, int op); //Function pointer to assembler function 
	//int relative_args []; //array of 0 or 1 to set relative arguments
	ARG_TEMPLATE *arg_templates [];
} INS_NODE_TEMPLATE;

typedef struct
{
	int op;
	ARG_TABLE args;
} INS_NODE;

typedef struct
{
	int val;
	char* name;
} KEYWORD;

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

/*TYPES of symbols*/
#define TYPE_LABEL      0x00
#define TYPE_DEF        0x01
#define TYPE_REG        0x02
#define TYPE_DONT_CARE  0xffae

//Register clases Classess
#define CLASS_GPR  0
#define CLASS_SPR  1
#define CLASS_SEC  2

#endif
