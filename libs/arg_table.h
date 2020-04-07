#pragma once
#include <stdbool.h>

#define INIT_ARG_TABLE_CP 0xff 

typedef struct 
{
    int value;
    int type;
} ARG_NODE;

typedef struct
{
    bool wait_slot;
    int size;
    int capacity;
    ARG_NODE* data;
} ARG_TABLE;

typedef struct
{
    int val;
    int type;
} MATCHED_ARG;


void init_arg_table(ARG_TABLE* arg_table);
void delete_arg_table();
void append_arg(ARG_TABLE* arg_table, MATCHED_ARG arg_match);
void search_node();