#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FILE_TABLE_INIT_CP 256

typedef struct
{
    char* data;
    char* name;
    size_t size; //Data lenght
} FILE_NODE;

typedef struct
{
    int size;
    int capacity;
    FILE_NODE* data;
    bool wait_slot;
} FILE_TABLE;

void init_file_table(FILE_TABLE* file_table);
void append_file(FILE_TABLE* file_table, char* name);
FILE_NODE* search_file(FILE_TABLE* file_table, char* name);
void delete_table(FILE_TABLE* file_table);