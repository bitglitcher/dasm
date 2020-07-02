#pragma once
#include <stdbool.h>
#define INIT_ARG_TABLE_CP 0xff 

//ARG NODE TEMPLATE

typedef struct
{
	char* name;
	int value;
	char* domain;
} ARG_NODE_TEMPLATE;

typedef struct
{
	int size;
	char* templates [];
} ARG_TEMPLATE;

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
    ARG_NODE_TEMPLATE* data;
} ARG_TABLE;

typedef struct
{
    int val;
    int type;
} MATCHED_ARG;


void init_arg_table(ARG_TABLE* arg_table);
void delete_arg_table();
void append_arg(ARG_TABLE* arg_table, ARG_NODE_TEMPLATE arg_match);
void search_node();
