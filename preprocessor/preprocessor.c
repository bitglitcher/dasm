#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char* remove_line_comment(char *str, size_t size)
{
	char *copy = malloc(sizeof(char*) * size);
	memmove(copy, str, size);
	//Scan letter by letter on the buffer
	for(size_t i = 0;i <= size;i++)
	{
		//printf("Argument %s\n", *(str_copy + i));
		if(*(str + i) == '/')
		{
			if(*(str + (i + 1)) == '/')
			{
				//Just fill with spaces
				int fill = 0;
				while(*(str + (fill + i)) != '\n' || *(str + (fill + i)) == '\0')
				{
					*(copy + (fill + i)) = ' ';
					fill++;
				}
			}
		}
		//printf("Nothing found\n");
	}
	return copy;
}
char *remove_block_comment(char *str, size_t size)
{
	char *copy = malloc(sizeof(char*) * size);
	memmove(copy, str, size);
	//Scan letter by letter
	for(size_t i = 0;i <= size;i++)
	{
		if(*(str + i) == '/')
		{
			if(*(str + (i + 1)) == '*')
			{
				//Fill with spaces until the close token
				int fill = 0;
				while(!(*(str + (fill + i)) == '*' && *(str + (fill + i + 1)) == '/'))
				{
					if(*(str + (fill + i)) == '\n')
					{
						*(copy + (i + fill)) = '\n';
					}
					else
					{
						*(copy + (i + fill)) = ' ';
					}
					fill++;
					//Buffer overflow protection
					if((i + fill) > size) return NULL;
					//So if it doesn't find a close token, this will return NULL
				}
				//Manually Delete the last two characters
				*(copy + (i + fill)) = ' ';
				*(copy + (i + fill + 1)) = ' ';
			}
		}
	}
	return copy;
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
