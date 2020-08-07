//This file describes the contents of the generated object files
//

typedef struct
{
    int pointer;
    int size;
    char* name;
} RELOC;

typedef struct
{
    int size;
    RELOC* reloc; //Reloc Entry
} RELOC_TABLE;

typedef struct
{
    RELOC_TABLE reloc_table;
    int size;
    char* binary_data;
} OBJ_FILE;


//Functions to serialize the object file struct
FILE* serialize(char* name, OBJ_FILE* obj_file);
