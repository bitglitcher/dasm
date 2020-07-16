#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bin_buffer.h"



void append_byte(BIN_BUFFER* bin_buffer, char byte)
{
    //Take wait slot
    if(bin_buffer->wait_slot)
    {
        bin_buffer->wait_slot = false;
    }
    else
    {
        bin_buffer->size++;
    }
    //Check capacity
    if(bin_buffer->size >= bin_buffer->capacity)
    {
        bin_buffer->capacity *= 2;
        bin_buffer->data = realloc(bin_buffer->data, sizeof(char) * bin_buffer->capacity);
    }

    //Apend data
    bin_buffer->data[bin_buffer->size]  = byte;
}

void init_buffer(BIN_BUFFER_TABLE* bin_buffer_table)
{
    bin_buffer_table->capacity = INIT_BUFFER_TABLE_CP;
    bin_buffer_table->size = 0;
    bin_buffer_table->wait_slot = true;
    bin_buffer_table->data = malloc(sizeof(BIN_BUFFER) * INIT_BUFFER_TABLE_CP);
}

void append_buffer(BIN_BUFFER_TABLE* bin_buffer_table, BIN_BUFFER* bin_buffer)
{
    //Take wait slot
    if(bin_buffer_table->wait_slot)
    {
        bin_buffer_table->wait_slot = false;
    }
    else
    {
        bin_buffer_table->size = bin_buffer_table->size + 1;
    }
    //Double capacity if full
    if(bin_buffer_table->size > bin_buffer_table->capacity)
    {
        bin_buffer_table->capacity = bin_buffer_table->capacity * 2;
        bin_buffer_table->data = realloc(bin_buffer_table->data, sizeof(BIN_BUFFER*) * bin_buffer_table->capacity);
    }

    //memcpy(bin_buffer_table->data + bin_buffer_table->size, bin_buffer, sizeof(BIN_BUFFER*) );
    *(bin_buffer_table->data + bin_buffer_table->size) = *bin_buffer;
}


BIN_BUFFER* search_table(BIN_BUFFER_TABLE* bin_buffer_table, char* name)
{
    if(bin_buffer_table)
    {
        //Loop til matched name
        for(int i = 0;i <= bin_buffer_table->size;i++)
        {
            //Check if node exists
            if(bin_buffer_table->data + i)
            {
                //Check is the name exists
                if(bin_buffer_table->data[i].name)
                {
                    //Compare both strings 
                    if(strcmp(bin_buffer_table->data[i].name, name) == 0)
                    {
                        return bin_buffer_table->data + i;
                    }
                }
            }
        }
    }
    //Else if not found return NULL
    return NULL;
}
void delete_buffer(BIN_BUFFER_TABLE* bin_buffer_table);


