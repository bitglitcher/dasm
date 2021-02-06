#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


//Return Modified Buffer
char* remove_line_comment(char *str, size_t size)
{
	char* new_buffer = malloc(sizeof(char) * size);
	memcpy(new_buffer, str, size);

	for(int i = 0;i <= size;i++)
	{
		if(*(new_buffer + i) == '/')
		{
			if((i + 1) < size)
			{
				if(*(new_buffer + i + 1) == '/')
				{
					//Search for endline and EOF
					if(memchr(new_buffer + i, '\n', (size - i)))
					{
						char* ocurrence = memchr(new_buffer + i, '\n', (size - i));
						memset(new_buffer + i, ' ', (ocurrence - new_buffer) - i);
					}
					else if(memchr(new_buffer + i, '\0', ((size - i) + 1)))
					{
						char* ocurrence = memchr(new_buffer + i, '\0', ((size - i) + 1));
						memset(new_buffer + i, ' ', (ocurrence - new_buffer) - i);
					}
					else if(memchr(new_buffer + i, EOF, ((size - i) + 1)))
					{
						char* ocurrence = memchr(new_buffer + i, EOF, ((size - i) + 1));
						memset(new_buffer + i, ' ', (ocurrence - new_buffer) - i);
					}					
				}
			}
		}
	}
	return new_buffer;
}

//Remove GNU AS like line comment
char* remove_gnu_as_comment(char* str, size_t size)
{
	char* new_buffer = malloc(sizeof(char) * size);
	memcpy(new_buffer, str, size);

	for(int i = 0;i <= size;i++)
	{
		if(*(new_buffer + i) == '#')
		{
			//Search for endline and EOF
			if(memchr(new_buffer + i, '\n', (size - i)))
			{
				char* ocurrence = memchr(new_buffer + i, '\n', (size - i));
				memset(new_buffer + i, ' ', (ocurrence - new_buffer) - i);
			}
			else if(memchr(new_buffer + i, '\0', ((size - i) + 1)))
			{
				char* ocurrence = memchr(new_buffer + i, '\0', ((size - i) + 1));
				memset(new_buffer + i, ' ', (ocurrence - new_buffer) - i);
			}
			else if(memchr(new_buffer + i, EOF, ((size - i) + 1)))
			{
				char* ocurrence = memchr(new_buffer + i, EOF, ((size - i) + 1));
				memset(new_buffer + i, ' ', (ocurrence - new_buffer) - i);
			}					
		}
	}
	return new_buffer;
}

//Returns Modified Buffer
char *remove_block_comment(char *str, size_t size)
{
	char* new_buffer = malloc(sizeof(char) * size);
	memcpy(new_buffer, str, size);

	for(int i = 0;i <= size;i++)
	{
		if(*(new_buffer + i) == '/')
		{
			if((i + 1) < size)
			{
				if(*(new_buffer + i + 1) == '*')
				{
					//Search for */
					if(((i + 2) < size) & ((i + 3) < size))
					{
						if(memchr(new_buffer + i + 2, '*', (size - i + 2)))
						{
							char* first_part = memchr(new_buffer + i + 2, '*', (size - (i + 2)));
							if(memchr(first_part + 1, '/', (size - (i + 3))))
							{
								char* ocurrence = memchr(first_part + 1, '/', (size - (i + 3)));
								memset(new_buffer + i, ' ', (ocurrence - new_buffer) - i + 1);
							}
						}
					}
				}
			}
		}
	}
	return new_buffer;
}

char *cnvrt_schar(char *str, size_t size)
{
	char *copy = malloc(sizeof(char*) * size);
	memmove(copy, str, size);
	//Scan letter by letter
	for(size_t i = 0;i <= size;i++)
	{
		if(*(copy + i) == '\\')
		{
			if(*(copy + (i + 1)) == 'n')
			{
				//Shift to eliminate
				*(copy + (i)) = '\n';
				*(copy + (i + 1)) = ' ';
				for(size_t x = 0; *(copy + ((i + x) + 1)) != '\0';x++)
				{
					*(copy + ((i + x) + 1)) = *(copy + ((i + x) + 2));
				}
				//Manually Delete the last two characters
			}
		}
		if(*(copy + i) == '\\')
		{
			if(*(copy + (i + 1)) == 't')
			{
				//Shift to eliminate
				*(copy + (i)) = '\t';
				*(copy + (i + 1)) = ' ';
				for(size_t x = 0; *(copy + ((i + x) + 1)) != '\0';x++)
				{
					*(copy + ((i + x) + 1)) = *(copy + ((i + x) + 2));
				}
				//Manually Delete the last two characters
			}
		}
	}
	return strdup(copy);
}

//int main()
//{
//	char *test = "hola //que tal\n Hola qur tal /*This Should Not be eliminated*/ la /*ja*/ vida //hahaha";
//	printf("Not modified: %s\n",test);
//	test = remove_line_comment(test, strlen(test));
//	printf("Modified: %s\n",test);
//	test = remove_block_comment(test, strlen(test));
//	printf("Modified: %s\n",test);
//
//	return 0;
//}
