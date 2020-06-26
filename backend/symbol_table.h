#ifndef symbol_table_def
#define symbol_table_def

#include <stdio.h>
#include <stdbool.h>

#define SYMBOL_TABLE_INIT_CP 0xff
#define LIST_INIT_CP 64

typedef struct
{
    int val;
    char* identifier;
    int type; //Just to diferentiate between val and identifier
} LIST_NODE;

typedef struct
{
    LIST_NODE* data;
    int capacity;
    int size;
    bool wait_slot;
} LIST;

typedef struct
{
    int type; 
    char* name;
    int addr;
    char* domain; //for tags inside of defs
    int scope_type;
    int size;
    int capacity;
    bool wait_slot;
    //Points to the list of the source attributes
    LIST* list;
} SYMBOL_NODE;


typedef struct
{
    SYMBOL_NODE* data;
    int capacity;
    int size;
    bool wait_slot;
} SYMBOL_TABLE;

void init_symbol_table(SYMBOL_TABLE* symbol_table);
void init_list(LIST* list);
LIST* create_list();
void append_to_list(LIST* list, int val, char* identifier, int type);
void delete_list(LIST* list);
void delete_symbol_table();
void append_symbol(SYMBOL_TABLE* symbol_table, char* name, int type, int addr, char* domain, int scope_type);
void append_symbol_with_list(SYMBOL_TABLE* symbol_table, char* name, int type, int addr, char* domain, int scope_type, LIST* list);
SYMBOL_NODE* search_symbol(SYMBOL_TABLE* symbol_table, char* name, char* domain);
void reset_symbol_table(SYMBOL_TABLE* symbol_table);
void append_tables(SYMBOL_TABLE* symbol_table_0, SYMBOL_TABLE* symbol_table_1);
#endif
