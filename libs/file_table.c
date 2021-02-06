#include "file_table.h"
#include "terminal_colors.h"
#include "../preprocessor/preprocessor.h"
#include "../debug.h"

void init_file_table(FILE_TABLE* file_table)
{
    //Set initial capacity
    file_table->capacity = FILE_TABLE_INIT_CP;
    file_table->size = 0;
    file_table->wait_slot = false;
    file_table->data = malloc(sizeof(FILE_NODE) * FILE_TABLE_INIT_CP);
}

void append_file(FILE_TABLE* file_table, char* name)
{
    if(file_table->wait_slot == true)
    {
        file_table->wait_slot = false;
    }
    else
    {
        file_table->size++;
    }    
    //Double capacity if full
    if(file_table->size >= file_table->capacity)
    {
        file_table->capacity *= 2;
        file_table->data = realloc(file_table->data, sizeof(FILE_NODE) * file_table->capacity);
    }
    //Open file
    FILE* file_ptr;
    file_ptr = fopen(name, "rb");
    if(!file_ptr)
    {
        printf(ANSI_COLOR_RED "error " ANSI_COLOR_RESET "No such file or directory\n");
        exit(0);
    }
    else
    {
        #ifdef _DEBUG_
            printf("\nallocating file\n");
        #endif
        //Get file size
        fseek (file_ptr, 0, SEEK_END);   // non-portable
        long file_size = ftell(file_ptr);
        file_table->data[file_table->size].size = (size_t)file_size;
        //Go to the begining
        rewind (file_ptr);
        #ifdef _DEBUG_
        printf("file size: %d\n", file_size);
        #endif
        char* mem_block = malloc(sizeof(char) * file_size);
        //Now copy the data to the buffer
        size_t read_bytes = fread(mem_block, sizeof(char), file_size, file_ptr);
        if(read_bytes != file_size)
        {
            printf("dasm: "ANSI_COLOR_RED "error: " ANSI_COLOR_RESET "reading file\n");
            exit(0);
        }
        if(!mem_block)
        {
            printf("dasm: "ANSI_COLOR_RED "error: " ANSI_COLOR_RESET "allocating memory\n");
            exit(0);
        }
        #ifdef _DEBUG_
        printf("contents in memory %s\n", mem_block);
        #endif
        fclose(file_ptr);

        //Preprocess files
        //Remove single line comments
        mem_block = remove_line_comment(mem_block, file_size);
        
        //Remove multiline comments
        mem_block = remove_block_comment(mem_block, file_size); 
        
        //Remove GNU Assembly like comments
        mem_block = remove_gnu_as_comment(mem_block, file_size); 

        #ifdef _DEBUG_
        printf("contents in memory %s\n", mem_block);
        #endif
        //Apend it to a file node
        file_table->data[file_table->size].data = strdup(mem_block);
        free(mem_block);
        file_table->data[file_table->size].name = strdup(name);
        return;
    }
}
FILE_NODE* search_file(FILE_TABLE* file_table, char* name)
{
    if(file_table)
    {
        for(int i = 0;i <= file_table->size;i++)
        {
            //Check node exists
            if((file_table->data + i) != NULL)
            {
                //check if name filed not NULL
                if(file_table->data[i].name)
                {
                    if(strcmp(file_table->data[i].name, name) == 0)
                    {
                        return (file_table->data + i);
                    }
                }
            }
        }
    }
    return NULL;
}

void delete_table(FILE_TABLE* file_table)
{
    if(!file_table)
    {
        for(int i = 0;i <= file_table->size;i++)
        {
            free(file_table->data[i].data);
            free(file_table->data[i].name);
        }
    }
    free(file_table->data);
}
