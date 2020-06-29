#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symbol_table.h"


void init_symbol_table(SYMBOL_TABLE* symbol_table)
{
	printf("Initializing Symbol Table\n");
	printf("Symbol Table INIT CP: %d\n", SYMBOL_TABLE_INIT_CP);
	symbol_table->capacity = SYMBOL_TABLE_INIT_CP;
	symbol_table->size = 0;
	symbol_table->wait_slot = true;
	symbol_table->data = malloc(sizeof(SYMBOL_NODE) * SYMBOL_TABLE_INIT_CP);
}

void init_list(LIST* list)
{
	list->size = 0;
	list->capacity = LIST_INIT_CP;
	list->wait_slot = true;
	list->data = malloc(sizeof(LIST_NODE) * LIST_INIT_CP);
}

LIST* create_list()
{
	LIST* new_list = malloc(sizeof(LIST));
	init_list(new_list);
	return new_list;
}

void append_to_list(LIST* list, int val, char* identifier, int type)
{
	if(list->wait_slot)
	{
		list->wait_slot = false;
	}
	else
	{
		list->size++;
	}
	//Check list size
	if(list->size >= list->capacity)
	{
		list->capacity *= 2;
		list->data = realloc(list->data, sizeof(LIST_NODE) * list->capacity);
	}

	list->data[list->size].identifier = identifier;
	list->data[list->size].val = val;
	list->data[list->size].type = type;

}

void delete_symbol_table()
{

}

void append_symbol(SYMBOL_TABLE* symbol_table, char* name, int type, int addr, char* domain, int scope_type)
{
	if(symbol_table->wait_slot == true)
	{
		symbol_table->wait_slot = false;
	}
	else
	{
		symbol_table->size++;
	}
	//Check size
	if(symbol_table->size >= symbol_table->capacity)
	{
		symbol_table->capacity *= 2;
		printf("Reallocating: %d\n", symbol_table->capacity);
		symbol_table->data = realloc(symbol_table->data, sizeof(SYMBOL_NODE) * symbol_table->capacity);
	}

	symbol_table->data[symbol_table->size].name = strdup(name);
	symbol_table->data[symbol_table->size].domain = strdup(domain);
	symbol_table->data[symbol_table->size].scope_type = scope_type;
	symbol_table->data[symbol_table->size].type = type;    
	symbol_table->data[symbol_table->size].addr = addr;
}

void append_symbol_with_list(SYMBOL_TABLE* symbol_table, char* name, int type, int addr, char* domain, int scope_type, LIST* list)
{
	if(symbol_table->wait_slot == true)
	{
		symbol_table->wait_slot = false;
	}
	else
	{
		symbol_table->size++;
	}
	//Check size
	if(symbol_table->size >= symbol_table->capacity)
	{
		symbol_table->capacity *= 2;
		printf("Reallocating: %d\n", symbol_table->capacity);
		symbol_table->data = realloc(symbol_table->data, sizeof(SYMBOL_NODE) * symbol_table->capacity);
	}

	symbol_table->data[symbol_table->size].name = strdup(name);
	symbol_table->data[symbol_table->size].domain = strdup(domain);
	symbol_table->data[symbol_table->size].type = type;    
	symbol_table->data[symbol_table->size].addr = addr;
	symbol_table->data[symbol_table->size].list = list;
	symbol_table->data[symbol_table->size].scope_type = scope_type;
}

SYMBOL_NODE* search_symbol(SYMBOL_TABLE* symbol_table, char* name, char* domain)
{
	//Check if table exist xdxdxd
	if(symbol_table)
	{
		//Now loop throught the whole thing
		for(int i = 0;i <= symbol_table->size;i++)
		{
			//Check node exists
			if((symbol_table->data + i) != NULL)
			{
				//Compare node atributtes
				if((strcmp(symbol_table->data[i].name, name) == 0) && (strcmp(symbol_table->data[i].domain, domain) == 0))
				{
					return (symbol_table->data + i);
				}
			}
		}
	}
	//If nothing found return NULL
	return NULL;
}

/*This function will only reset the index pointer, not delete the table*/
void reset_symbol_table(SYMBOL_TABLE* symbol_table)
{
	//Data will not be deleted, so it will have garbage
	symbol_table->wait_slot = true;
	symbol_table->size = 0;
}

/*This function will append table 1 to table 0*/
void append_tables(SYMBOL_TABLE* symbol_table_0, SYMBOL_TABLE* symbol_table_1)
{
	if(symbol_table_0 && symbol_table_1)
	{
		for(int i = 0;i <= symbol_table_1->size;i++)
		{
			if(symbol_table_1->data)
			{
				append_symbol(symbol_table_0, symbol_table_1->data[i].name, symbol_table_1->data[i].type, symbol_table_1->data[i].addr, symbol_table_1->data[i].domain, symbol_table_1->data[i].scope_type);
			}
		}
	}
}
