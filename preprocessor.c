#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void remove_single_line_comment(char* buffer);
void remove_multi_line_comment(char* buffer);
void remove_defines(char* buffer);
void remove_includes(char* buffer);
void process_macros(char* buffer);

int main()
{
    char* buffer = "#define HOLA\n HOLA";


    return 0;
}