#ifndef symbol_table_def
#define symbol_table_def

#include <stdio.h>
#include <stdbool.h>

#define SYMBOL_TABLE_INIT_CP 0xff

typedef struct
{
    int type; 
    char* name;
    int addr;
    char* domain; //for tags inside of defs
} SYMBOL_NODE;

typedef struct
{
    SYMBOL_NODE* data;
    int capacity;
    int size;
    bool wait_slot;
} SYMBOL_TABLE;

void init_symbol_table(SYMBOL_TABLE* symbol_table);
void delete_symbol_table();
void append_symbol(SYMBOL_TABLE* symbol_table, char* name, int type, char* domain);
SYMBOL_NODE* search_symbol(SYMBOL_TABLE* symbol_table, char* name, char* domain);
void reset_symbol_table(SYMBOL_TABLE* symbol_table);

#endif