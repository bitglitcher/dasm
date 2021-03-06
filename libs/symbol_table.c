#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symbol_table.h"
#include "../debug.h"

void init_symbol_table(SYMBOL_TABLE* symbol_table)
{
    symbol_table->capacity = SYMBOL_TABLE_INIT_CP;
    symbol_table->size = 0;
    symbol_table->wait_slot = true;
    symbol_table->data = malloc(sizeof(SYMBOL_NODE) * SYMBOL_TABLE_INIT_CP);
}



void delete_symbol_table()
{

}

void append_symbol(SYMBOL_TABLE* symbol_table, char* name, int type, int addr, char* domain)
{
    if(symbol_table->wait_slot == true)
    {
        symbol_table->wait_slot = false;
    }
    else
    {
        symbol_table->size++;
    }
    //Check size
    if(symbol_table->size >= symbol_table->capacity)
    {
        symbol_table->capacity *= 2;
        symbol_table->data = realloc(symbol_table->data, sizeof(SYMBOL_NODE) * symbol_table->capacity);
    }

    symbol_table->data[symbol_table->size].name = strdup(name);
    symbol_table->data[symbol_table->size].domain = strdup(domain);
    symbol_table->data[symbol_table->size].type = type;    
    symbol_table->data[symbol_table->size].addr = addr;
}

SYMBOL_NODE* search_symbol(SYMBOL_TABLE* symbol_table, char* name, char* domain)
{
    //Check is table exist xdxdxd
    if(symbol_table)
    {
        //Now loop throught the whole thing
        for(int i = 0;i <= symbol_table->size;i++)
        {
            //Check node exists
            if((symbol_table->data + i) != NULL)
            {
                //Compare node atributtes
                if((strcmp(symbol_table->data[i].name, name) == 0) && (strcmp(symbol_table->data[i].domain, domain) == 0))
                {
                    return (symbol_table->data + i);
                }
            }
        }
    }
    //If nothing found return NULL
    return NULL;
}

/*This function will only reset the index pointer, not delete the table*/
void reset_symbol_table(SYMBOL_TABLE* symbol_table)
{
    symbol_table->wait_slot = true;
    symbol_table->size = 0;
    //Data will not be reseted, so it will have garbage
}

/*This function will append table 1 to table 0*/
void append_tables(SYMBOL_TABLE* symbol_table_0, SYMBOL_TABLE* symbol_table_1)
{
    if(symbol_table_0 && symbol_table_1)
    {
        for(int i = 0;i <= symbol_table_1->size;i++)
        {
            if(symbol_table_1->data)
            {
                append_symbol(symbol_table_0, symbol_table_1->data[i].name, symbol_table_1->data[i].type, symbol_table_1->data[i].addr, symbol_table_1->data[i].domain);
            }
        }
    }
}