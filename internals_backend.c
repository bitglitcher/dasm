#include <stdio.h>
#include <string.h>
#include "internals.h"
#include "libs/arg_table.h"
#include "internals_backend.h"
#include "libs/symbol_table.h"
#include "arch/d16i.h"


/*Have to be defined*/
char* regs [] = REGS_NAMES;
int reg_addr [] = REGS_ADDRS; 

/*keyword specific to the architecture*/
char* target_keywords [] = TARGET_KEYWORDS;
int target_keywords_vals [] = TARGET_KEYWORDS_VALS;
int target_keywords_type [] = TARGET_KEYWORDS_TYPES;

/*ALSO a the number of keywords has to be specified*/
//#define NTARGET_KEYWORDS

void init_internal_backend()
{

}

//Instruction template array
INS_NODE_TEMPLATE* instructions [] = INS_TEMPLATE_ARRAY;

INS_NODE_TEMPLATE* get_duplicate(char* name, int offset)
{
    for(int i = offset + 1;i <= N_INS_TEMPLATES - 1;i++)
    {
        INS_NODE_TEMPLATE* ptr = instructions[i];
        printf("template name: %s\n", ptr->name);
        printf("identifier name: %s\n", name);
        if(strcmp(ptr->name, name) == 0)
        {
            return ptr;
        }
    }
}

INS_NODE_TEMPLATE* get_duplicate_index(char* name, int offset)
{
    for(int i = offset + 1;i <= N_INS_TEMPLATES - 1;i++)
    {
        INS_NODE_TEMPLATE* ptr = instructions[i];
        printf("template name: %s\n", ptr->name);
        printf("identifier name: %s\n", name);
        if(strcmp(ptr->name, name) == 0)
        {
            return i;
        }
    }
    return NULL; //If nothing was found
}

/*The symbol table will have the array of arguments*/
void assemble_ins(char* name , ARG_TABLE* arg_table)
{
    INS_NODE_TEMPLATE* saved;
    printf("Assemble ins %s\n", name);
    for(int i = 0;i <= N_INS_TEMPLATES - 1;i++)
    {
        INS_NODE_TEMPLATE* ptr = instructions[i];
        printf("template name: %s\n", ptr->name);
        printf("identifier name: %s\n", name);
        if(strcmp(ptr->name, name) == 0)
        {
            printf("\t\tMatch Found\n");
            saved = ptr;
            //Now check for correct syntax
            if(arg_table->size == (ptr->nargs - 1))
            {
                printf("\t\t\t%s detected\n", ptr->name);
                //Call assembler function and provide context
                (*ptr->asm_func)(NULL, arg_table, ptr->op);
                return; //Done with assembling
            }
            else
            {
                printf("\t\tIteration to find overriden template\n");
            }
        }
    }
    //If there was an ocurrence
    if(saved)
    {
        if(arg_table->size > (saved->nargs - 1))
        {
            printf("\t\tError: too many arguments %d\n", arg_table->size);
        }
        else
        {
            printf("\t\tError: more arguments expected %d\n", arg_table->size);
        }
    }
    //If not found check for defenitions IDK
}

extern SYMBOL_TABLE symbol_table; //Global symbol table

MATCHED_ARG match_args(char* name)
{
    MATCHED_ARG arg_match;
    /*This is for the registers*/
    for(int i = 0;i <= NREGS - 1;i++)
    {
        if(regs [i])
        {
            if(strcmp(regs[i], name) == 0)
            {
                arg_match.val  = reg_addr [i]; 
                return arg_match;
            }
        }
    }
    /*Target Specific Keywords*/
    for(int i = 0;i <= N_TARGET_KEYWORDS - 1;i++)
    {
        if(strcmp(target_keywords [i], name) == 0)
        {
            arg_match.val = target_keywords_vals [i];
            return arg_match;
        }
    }
    /*Symbol table search*/
    SYMBOL_NODE* symbol_node = search_symbol(&symbol_table, name, "none");
    if(symbol_node)
    {
        arg_match.val =  symbol_node->addr;
        return arg_match;
    }
    printf("Invalid argument: default 0x0000\n");
    arg_match.val = 0;
    return arg_match;
}

bool wait_slot_addr_inc = true;
void increment_addr()
{
    if(wait_slot_addr_inc)
    {
        wait_slot_addr_inc = false;
    }
    else
    {
        addr += NADDR_INS;
    }
    
}