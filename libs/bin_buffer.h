#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define INIT_BUFFER_TABLE_CP 0xff

typedef struct 
{    
    int size;
    int capacity;
    char* data;
    char* name;
    bool wait_slot;
} BIN_BUFFER;

typedef struct 
{
    int size;
    int capacity;
    BIN_BUFFER* data;
    bool wait_slot;
} BIN_BUFFER_TABLE;


void append_byte(BIN_BUFFER* bin_buffer, char byte);
void init_buffer(BIN_BUFFER_TABLE* bin_buffer_table);
void append_buffer(BIN_BUFFER_TABLE* bin_buffer_table, BIN_BUFFER* bin_buffer);
BIN_BUFFER* search_table(BIN_BUFFER_TABLE* bin_buffer_table, char* name);
void delete_buffer(BIN_BUFFER_TABLE* bin_buffer_table);