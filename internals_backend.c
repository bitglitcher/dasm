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


void init_internal_backend()
{

}

//Instruction template array
INS_NODE_TEMPLATE* instructions [] = INS_TEMPLATE_ARRAY;

/*The symbol table will have the array of arguments*/
void assemble_ins(char* name , ARG_TABLE* arg_table)
{
    printf("Assemble ins %s\n", name);
    for(int i = 0;i <= N_INS_TEMPLATES - 1;i++)
    {
        INS_NODE_TEMPLATE* ptr = instructions[i];
        printf("template name: %s\n", ptr->name);
        printf("identifier name: %s\n", name);
        if(strcmp(ptr->name, name) == 0)
        {
            printf("\t\tMatch Found\n");
            //Now check for correct syntax
            if(arg_table->size == (ptr->nargs - 1))
            {
                printf("\t\t\t%s detected\n", ptr->name);
                //Call assembler function and provide context
                (*ptr->asm_func)(NULL, arg_table, ptr->op);
            }
            else
            {
                if(arg_table->size > (ptr->nargs - 1))
                {
                    printf("\t\tError: too many arguments %d\n", arg_table->size);
                }
                else
                {
                    printf("\t\tError: more arguments expected %d\n", arg_table->size);
                }
                
            }
            
        }
    }
}


int match_args(char* name)
{
    /*This is for the registers*/
    for(int i = 0;i <= NREGS - 1;i++)
    {
        if(regs [i])
        {
            if(strcmp(regs[i], name) == 0)
            {
                return reg_addr [i]; 
            }
        }
    }
    printf("Invalid argument: default 0x0000\n");
    return 0;
}