#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arg_table.h"
#include "../internals_backend.h"

void init_arg_table(ARG_TABLE* arg_table)
{
    printf("\t\tINIT ARG TABLE\n");
    arg_table->capacity = INIT_ARG_TABLE_CP;
    arg_table->wait_slot = true;
    arg_table->size = 0;
    arg_table->data = malloc(sizeof(ARG_NODE) * INIT_ARG_TABLE_CP);
}

void delete_arg_table()
{

}

void append_arg(ARG_TABLE* arg_table, MATCHED_ARG arg_match)
{
    if(arg_table->wait_slot)
    {
        arg_table->wait_slot = false;
    }
    else
    {
        arg_table->size++;
    }

    //Check capacity
    if(arg_table->size >= arg_table->capacity)
    {
        arg_table->capacity *= 2;
        arg_table->data = realloc(arg_table->data, sizeof(ARG_NODE) * arg_table->capacity);
    }

    //Now append
    arg_table->data[arg_table->size].value = arg_match.val;
    arg_table->data[arg_table->size].type = arg_match.type;
}


void search_node()
{

}