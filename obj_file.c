#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "obj_file.h"
#include "libs/terminal_colors.h"


FILE* serialize(char* name, OBJ_FILE* obj_file)
{
    //Open File
    FILE* file = fopen(name, "w+");

    //Write to file OBJ_FILE
    //size_t fwrite ( const void * ptr, size_t size, size_t count, FILE * stream );
    if(file == NULL)
    {
        printf("dasm: " ANSI_COLOR_RED "fatal error" ANSI_COLOR_RESET ": creating object file\n");
        return NULL; 
    }
    else
    {
        //Calculate the lenght of all RELOC strings
        int reloc_names_size = 0;
        for(int i = 0;i <= obj_file->reloc_table.size - 1;i++)
        {
            if(obj_file->reloc_table.reloc + i)
            {
                reloc_names_size += obj_file->reloc_table.reloc[i].size;
            }
        }
        //Allocate the memory for the buffer
        char* buffer = malloc(sizeof(OBJ_FILE) + obj_file->size + obj_file->reloc_table.size + reloc_names_size);

        //Serialize struct data into buffer
        memcpy(buffer, &obj_file->reloc_table.size, sizeof(int));
        int name_size = 0;
        for(int i = 0; i <= obj_file->reloc_table.size - 1;i++)
        {
            memcpy(buffer + sizeof(int) + (i * sizeof(RELOC)) + name_size, &obj_file->reloc_table.reloc[i].pointer, sizeof(int));
            memcpy(buffer + sizeof(int) + (i * sizeof(RELOC)) + sizeof(int) + name_size, &obj_file->reloc_table.reloc[i].size, sizeof(int));
            memcpy(buffer + sizeof(int) + (i * sizeof(RELOC)) + (sizeof(int) * 2) + name_size, obj_file->reloc_table.reloc[i].name, strlen(obj_file->reloc_table.reloc[i].name));
            name_size += strlen(obj_file->reloc_table.reloc[i].name);
        }
        memcpy(buffer + sizeof(int) + (obj_file->reloc_table.size * sizeof(RELOC)) + (sizeof(int) * 2) + name_size, &obj_file->size, sizeof(int));
        memcpy(buffer + sizeof(int) + (obj_file->reloc_table.size * sizeof(RELOC)) + (sizeof(int) * 3) + name_size, obj_file->binary_data, obj_file->size);
        
        //Write file
        fwrite(buffer, sizeof(char), sizeof(OBJ_FILE) + obj_file->size + obj_file->reloc_table.size + reloc_names_size, file);
    }
}
