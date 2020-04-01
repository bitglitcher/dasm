#pragma once
#include <stdbool.h>

#define INIT_ARG_TABLE_CP 0xff 

typedef struct 
{
    int value;
} ARG_NODE;

typedef struct
{
    bool wait_slot;
    int size;
    int capacity;
    ARG_NODE* data;

} ARG_TABLE;


void init_arg_table(ARG_TABLE* arg_table);
void delete_arg_table();
void append_arg(ARG_TABLE* arg_table, int value);
void search_node();