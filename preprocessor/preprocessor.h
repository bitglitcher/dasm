#ifndef __PREPROCESSOR_H__
#define __PREPROCESSOR_H__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define INIT_ENTRY_TABLE_SIZE 0xff

typedef struct
{
    char* name; //Define indentifier
    char* contents;
} define_entry_t;

typedef struct
{
    size_t size; //Always points to the last added entry index.
    size_t capacity;
    define_entry_t* define_entry;
} preprocessor_table_t;

extern char* remove_line_comment(char *str, size_t size);
extern char* remove_block_comment(char *str, size_t size);
extern char* remove_gnu_as_comment(char* str, size_t size);

extern void init_preprocessor(preprocessor_table_t* preprocessor_table);
extern void append_define(preprocessor_table_t* preprocessor_table,  char* name, char* contents);
extern define_entry_t* search_define(preprocessor_table_t* preprocessor_table,  char* name);
extern char* replace_string(char* dest, char* string, char* search);
extern void preprocess_memory(preprocessor_table_t* preprocessor_table, char* memory, size_t size);
extern char* replace_defines(char* memory, size_t size);

#endif