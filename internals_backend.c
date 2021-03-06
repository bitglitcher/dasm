#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "internals.h"
#include "libs/arg_table.h"
#include "internals_backend.h"
#include "libs/symbol_table.h"
#include "libs/terminal_colors.h"
#include "build/target.h"
#include "libs/bin_buffer.h"
#include "debug.h"

/*Have to be defined*/
//char* regs [] = REGS_NAMES;
//int reg_addr [] = REGS_ADDRS; 
extern int yylineno;
//These contain all the keywords from the target like registers and constants
ARG_NODE_TEMPLATE* arg_node_templates [] = ARG_NODES;

/*keyword specific to the architecture*/
//char* target_keywords [] = TARGET_KEYWORDS;
//int target_keywords_vals [] = TARGET_KEYWORDS_VALS;
//int target_keywords_type [] = TARGET_KEYWORDS_TYPES;

/*ALSO a the number of keywords has to be specified*/
//#define NTARGET_KEYWORDS

//REGISTER CLASSES
//int REG_CLASS [] = REG_CLASSES;

void init_internal_backend()
{
    for(int i = 0;i <= N_INS_TEMPLATES - 1;i++)
    {
        INS_NODE_TEMPLATE* ptr = instructions[i];
        //ptr->
    }
}

//Instruction template array
INS_NODE_TEMPLATE* instructions [] = INS_TEMPLATE_ARRAY;

INS_NODE_TEMPLATE* get_duplicate(char* name, int offset)
{
    for(int i = offset + 1;i <= N_INS_TEMPLATES - 1;i++)
    {
        INS_NODE_TEMPLATE* ptr = instructions[i];
        #ifdef _DEBUG_
        printf("template name: %s\n", ptr->name);
        printf("identifier name: %s\n", name);
        #endif
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
        #ifdef _DEBUG_
        printf("template name: %s\n", ptr->name);
        printf("identifier name: %s\n", name);
        #endif
        if(strcmp(ptr->name, name) == 0)
        {
            return ptr;
        }
    }
    return NULL; //If nothing was found
}

bool* check_types(ARG_TABLE* arg_table, INS_NODE_TEMPLATE* ins_node)
{
    //if(!ins_node->ntypes)
    //{
    //    printf("\t\t\t\t\tInstruction Node Argument Template Not Implemented\n");
    //    return (bool*)true;
    //}
    if(arg_table && ins_node)
    {
        #ifdef _DEBUG_
        printf("\t\t\t\tcheck type arguments allocated!\n");
        #endif

        //Because the number of elements on the arg_table and the instruction template
        //are the same, we can use a single for loop to address the two arrays
            if(arg_table->size != -1) //If not empty
            {
                for(int i = 0;i <= arg_table->size; i++)
                {
                    #ifdef _DEBUG_
                    printf("\t\t\t\tcheck types iteration!\n");
                    printf("\t\t\t\tINS_TEMPLATE name -> %s\n", ins_node->name);
                    printf("\t\t\t\t\tARG_NODE index -> %d\n", i);
                    #endif
                    for(int x = 0;x <= ins_node->arg_templates[i]->size;x++)
                    {
                        #ifdef _DEBUG_
                            printf("\t\t\t\t\tINS_ARG_TEMPLATE iteration: got %s, expected %s\n", arg_table->data[i].domain, ins_node->arg_templates[i]->templates[x]);
                        #endif
                        
                        //printf("\t\t\t\t\tGot domain -> %s\n", arg_table->data[i].domain);
                        if(strcmp(arg_table->data[i].domain, ins_node->arg_templates[i]->templates[x]) != 0)
                        {
                            if(strcmp(arg_table->data[i].domain, "numeric") == 0)
                            {
                                printf(ANSI_COLOR_RED "Error: " ANSI_COLOR_RESET "on line %d imcompatible argument 0x%x\n", yylineno, arg_table->data[i].value);
                            }
                            else
                            {
                                printf(ANSI_COLOR_RED "Error: " ANSI_COLOR_RESET "on line %d imcompatible argument %s\n", yylineno, arg_table->data[i].name);
                            }
                            printf(ANSI_COLOR_RED "Error: " ANSI_COLOR_RESET "on line %d imcompatible argument, expected argument %s, recieved %s\n", yylineno, ins_node->arg_templates[i]->templates[x], arg_table->data[i].domain);
                            //Print possible domains
                            //printf(ANSI_COLOR_GREEN "Possible Arguments:" ANSI_COLOR_RESET "\n");
                            return (bool*) false;
                        }
                    }
                }
            }
        }
    return (bool*)true;
}

/*The symbol table will have the array of arguments*/
void assemble_ins(char* name , ARG_TABLE* arg_table)
{
    INS_NODE_TEMPLATE* saved;
    #ifdef _DEBUG_
    printf("Assemble ins %s\n", name);
    #endif
    for(int i = 0;i <= N_INS_TEMPLATES - 1;i++)
    {
        INS_NODE_TEMPLATE* ptr = instructions[i];
        #ifdef _DEBUG_
        printf("\ttemplate name: %s\n", ptr->name);
        printf("\tidentifier name: %s\n", name);
        #endif
        if(strcmp(ptr->name, name) == 0)
        {
            #ifdef _DEBUG_
            printf("\t\tMatch Found\n");
            #endif
            saved = ptr;

            //Now check for correct syntax
            #ifdef _DEBUG_
            printf("\t\targ_table->size = %d\n", arg_table->size);
            printf("\t\t (ptr->n_templates - 1) = %d\n", (ptr->n_templates - 1));
            #endif
            if(arg_table->size == (ptr->n_templates - 1))
            {
                #ifdef _DEBUG_
                printf("\t\t\t%s detected\n", ptr->name);
                #endif
                //Before calling the assembler function, run syntax check
                if(check_types(arg_table, ptr))
                {
                    //Call assembler function and provide context
                    (*ptr->asm_func)(&bin_buffer, arg_table, ptr->op);
                    #ifdef _DEBUG_
                    printf("\t\t\t\tAssembler functions now implemented\n");
                    #endif
                    return; //Done with assembling
                }
                else 
                {    
                    #ifdef _DEBUG_
                    printf("\t\tIteration to find overriden template\n");
                    #endif
                }
            }
            else
            {
                #ifdef _DEBUG_
                printf("\t\tIteration to find overriden template\n");
                #endif
            }
        }
    }
    //If there was an ocurrence
    if(saved)
    {
        if(arg_table->size > (saved->nargs - 1))
        {
            printf(ANSI_COLOR_RED "Error:" ANSI_COLOR_RESET " on line %d too many arguments %d\n", yylineno, arg_table->size);
        }
        else
        {
            printf(ANSI_COLOR_RED "Error:" ANSI_COLOR_RESET " more arguments expected %d\n", arg_table->size);
        }
    }
    //If not found check for defenitions IDK
    //If there is no return at this point print errors
    //
    //
    //
    //
}

extern SYMBOL_TABLE symbol_table; //Global symbol table

ARG_NODE_TEMPLATE match_args(char* name)
{   
    ARG_NODE_TEMPLATE arg_node;
    //Match ARG_NODE_TEMPLATES with the correct name
    for(int i = 0;i <= N_ARG_NODES - 1;i++)
    {
        #ifdef _DEBUG_
        printf("Iterationg throught nodes %d -> %s\n", i, arg_node_templates[i]->name);
        #endif
        if(strcmp(arg_node_templates[i]->name, name) == 0)
        {
            #ifdef _DEBUG_
            printf("\tString found -> %s , %s\n", arg_node_templates[i]->name, name);
            #endif
            arg_node.domain = arg_node_templates[i]->domain;
            arg_node.name = arg_node_templates[i]->name;
            arg_node.value = arg_node_templates[i]->value;
            return arg_node; 
            break;
        }
    }

    //Symbol table search
    SYMBOL_NODE* symbol_node = search_symbol(&symbol_table, name, "none");
    if(symbol_node)
    {
        arg_node.value = symbol_node->addr;
        arg_node.name = symbol_node->name;
        arg_node.domain = symbol_node->domain;
        return arg_node;
    }
    printf("Invalid argument: default 0x0000\n");
    arg_node.value = 0;
    arg_node.domain = "invalid";
    arg_node.name = "invalid";
    return arg_node;

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
        //Hardcoded just for testing, should be CHANGED later
        addr += 2;//NADDR_INS;
    }

}

bool get_domain(char* domain)
{
    for(int i = 0;i <= N_ARG_NODES;i++)
    {
        if(strcmp(arg_node_templates[i]->domain, domain))
        {
            return true;
        }
    }
    return false; //If nothing was found
}
