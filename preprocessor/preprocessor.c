#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "preprocessor.h"


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

//Should only be called once to initialize the preprocessor define table
void init_preprocessor(preprocessor_table_t* preprocessor_table)
{
	preprocessor_table->size = -1; //Currently the size is set to 0, meaning that this buffer is empty
	preprocessor_table->define_entry = malloc(sizeof(preprocessor_table->define_entry) * preprocessor_table->size);
	preprocessor_table->capacity = INIT_ENTRY_TABLE_SIZE;
}

void append_define(preprocessor_table_t* preprocessor_table,  char* name, char* contents)
{
	if(preprocessor_table->capacity < preprocessor_table->size)
	{
		preprocessor_table->capacity *= 2; //Double capacity
		preprocessor_table->define_entry = realloc(preprocessor_table->define_entry, preprocessor_table->size * sizeof(define_entry_t));
	}
	preprocessor_table->size++;
	preprocessor_table->define_entry[preprocessor_table->size].name = name;
	preprocessor_table->define_entry[preprocessor_table->size].contents = contents;
}

define_entry_t* search_define(preprocessor_table_t* preprocessor_table,  char* name)
{
	for(int i = 0;i <= preprocessor_table->size;i++)
	{
		if(strcmp(preprocessor_table->define_entry[i].name, name) == 0) //Check if fies are the same
		{
			return &preprocessor_table->define_entry[i];
		}
	}
	//If no occurrence was found, just return null
	return NULL;
}

//If the string is found to be a whole identifier, and the it matches the
//search string, then it will be replaced by the string argument.
char* replace_string(char* buffer, char* string, char* search)
{
    //Legal character that are allowed as prefix or postfix leading characters
    char allowed [] = ",.!@#$/` ^&*()?><~+=[]{}:;\n";
    
    //Save old buffer
    char* copy = strdup(buffer);
    char* modified_buffer = strdup(buffer);
    //Find search match
    char* ptr = strstr(modified_buffer, search);
    int offset = (ptr - modified_buffer);
    while(ptr)
    {
        if(ptr)
    	{
    		//Try to match the whole string
    		if(memcmp(ptr, search, strlen(search)) == 0)
    		{
    			//Check posfix and prefix
    		    char* substring = search;
                bool prefix_legal = false;
                bool postfix_legal = false;
                for(int i = 0;i < strlen(allowed);i++)
                {
                    printf("%d %c %d\n", ptr, *ptr, modified_buffer);
                    if(ptr > modified_buffer)
                    {
                        if(*(ptr - 1) == allowed[i])
                        {
                            prefix_legal = true;
                        }
                    }
                    else
                    {
                        prefix_legal = true;
                    }
                    if((ptr + strlen(substring)) < modified_buffer)
                    {
                        if(*(ptr + strlen(substring) + 1) == allowed[i] || *(ptr + strlen(substring) + 1) == '\0')
                        {
                            postfix_legal = true;
                        }
                    }
                    else
                    {
                        postfix_legal = true;
                    }
                }
                if(prefix_legal && postfix_legal)
    			{
    				if(!modified_buffer)
    				{
    					modified_buffer = realloc(modified_buffer, sizeof(buffer) * (strlen(string) + strlen(buffer)));
    				}
    				else if((sizeof(modified_buffer) * (strlen(string) + strlen(modified_buffer))) > strlen(modified_buffer))
    				{
    					modified_buffer = realloc(modified_buffer, sizeof(buffer) * (strlen(string) + strlen(buffer)));
    				}
    				//printf("modified_buffer before: %s\n", modified_buffer);
    				//Proceed to replace the string
                    memcpy(modified_buffer, copy, strlen(string) + offset);
    				memcpy(modified_buffer + offset, string, strlen(string));
    				memcpy((modified_buffer + offset + strlen(string)), (copy + offset + strlen(substring)), strlen(copy) - (offset + strlen(substring)));
    	            ptr += strlen(search);
    				//printf("modified_buffer after: %s\n", modified_buffer);
    			}
    			else
    			{
                    ptr += strlen(search);
    			}
    		}
    	}
    	ptr = strstr(ptr, search);
    	offset = (ptr - modified_buffer);
    	memcpy(copy, modified_buffer, strlen(modified_buffer));
    }
    return modified_buffer;
}

void preprocess_memory(preprocessor_table_t* preprocessor_table, char* memory, size_t size)
{
	//Replace all defines with their respective deine_entry content
	for(int i = 0;i <= preprocessor_table->size;i++)
	{
		//Search first character occurence
		char* ptr = memchr(memory, *preprocessor_table->define_entry[i].name, size);
		if(ptr) //Check for a valid pointer
		{
			//Then try to compare string
			//Check if there are still memory bytes left, so it doesn't go into a unallocated memory region
			if((ptr-memory) <= size)
			{
				if(memcmp(memory, preprocessor_table->define_entry->name, strlen(preprocessor_table->define_entry[i].name)) == 0) //If contents are equal
				{
					//Then replace with the contents of the define entry
					char* copy = malloc(sizeof(memory) * (size + strlen(preprocessor_table->define_entry[i].name)));
					memcpy(copy, memory, size);
				}
			}
		}
	}

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
