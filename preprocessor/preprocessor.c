/*
This is a C like preprocessor, for the DASM assembler, written by Benjamin Herrera Navarro.
File created on 05/12/2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void remove_single_line_comment(char* buffer);
void remove_multi_line_comment(char* buffer);
void remove_defines(char* buffer);
void remove_includes(char* buffer);
void process_macros(char* buffer);




void remove_multiline_comment(char* buffer, int size)
{
	//Search for the /* token
	for(int i = 0;i <= size;i++)
	{
		if(*(buffer + i) == '/' & *(buffer + i++) '*')
		{
			
		}
	}
}

int main()
{
    char* buffer = "#define HOLA\n HOLA";


    return 0;
}
