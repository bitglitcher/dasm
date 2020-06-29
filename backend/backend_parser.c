/*
   Written by: Benjamin Herrera Navarro
   Backend interface lenguage
   */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"
#include "backend_parser_types.h"

//Define if the front end uses hardcoded architecture description
//#define BULTIN_PARSER


SYMBOL_TABLE symbol_table;

extern void reset_identifiers();
extern void yyparse();
extern void print_symbol_table();

#define DEFAULT_C_FILE "target.c"
#define DEFAULT_HEADER_FILE "target.h"

#define PROLOGUE_H "#ifndef _TARGET_\n#define _TARGET_\n\n#include \"../internals.h\"\n\n\n\n"

#define EPILOUGE_H "\n\n\n\n#endif\n"

//Define libraries to include in the target.c file
#define PROLOGUE_C "#include <stdio.h>\n#include <string.h>\n#include \"target.h\"\n\n"
#define EPILOGUE_C ""

//ARGUMENT NODE TEMPLATE STRUCTURE

#define ARG_TEMPLATE_PROLOUGE(name) ARG_NODE_TEMPLATE##name
#define ARG_TEMPLATE_EPILOGUE "}"

#define ARG_NODES_INFO "//Join all the ARG_NODE_TEMPLATE defenition into a pointer array,\n//so the assembler backend can reference the argument nodes\n"

#define INS_TEMPLATE_ARRAY_INFO "\n//Pointers to the instruction nodes, so the assembler can use them\n"

/*ARGUMENT NODE TEMPLATE STRUCTURE*/

/*
   typedef struct 
   {
   char* name;
   int type;
   int value;
   } ARG_NODE_TEMPLATE;

   The gen_keywords function will initialize the ARG_NODE_TEMPLATE
   structure 

   ARG_NODE_TEMPLATE "name" = {.name="name", .type="some_type", .value="somevalue", .domain="domain_name"};

*/

/* all tree gen functions will append data to the buffer argument*/
void gen_keywords(SYMBOL_TABLE* symbol_table, FILE* _c_file, FILE* _h_file)
{
	bool first = true;
	//all nodes within the scope_type of arg are keywords
	/*Better adding it to an struct with name and value*/
	printf("----------------ARG DOMAINS----------------\n");
	//extract and print all arg domains and create instaces of them
	if(symbol_table)
	{
		fputs("/*----------------KEYWORDS----------------*/\n", _c_file);
		fputs("/*----------------KEYWORDS----------------*/\n", _h_file);
		//fputs("char* taget_keywords = {", file);
		for(int i = 0;i <= symbol_table->size;i++)
		{
			if(symbol_table->data + i)
			{
				if(symbol_table->data[i].scope_type == TYPE_ARG & symbol_table->data[i].type == TYPE_IDENTIFIER)
				{                    
					printf("keyword found -> %s\n", symbol_table->data[i].name);
					//check is there is another element after this one
					fputs("ARG_NODE_TEMPLATE", _c_file);
					fprintf(_c_file, " %s = { .name = \"%s\", ", symbol_table->data[i].name, symbol_table->data[i].name);
					if(symbol_table->data[i].list)
					{
						//Store all values on an array for list
						fprintf(_c_file, ".value = %d,", symbol_table->data[i].list->data[0].val);
					}
					else
					{
						fputs(".value = NULL", _c_file);
					}

					fprintf(_c_file, " .domain = \"%s\"", symbol_table->data[i].domain);
					//fputs("}\n", file);
					fputs("};\n", _c_file);
				}
			}
		}
		fputc('\n', _c_file);
		//Now include every element into a pointer array
		fputs(ARG_NODES_INFO, _h_file);
		fputs("#define ARG_NODES {", _h_file);
		for(int i = 0;i <= symbol_table->size;i++)
		{
			if(symbol_table->data + i)
			{
				if(symbol_table->data[i].scope_type == TYPE_ARG & symbol_table->data[i].type == TYPE_IDENTIFIER)
				{
					if(first)
					{
						first = false;
					}
					else
					{
						fputs(", ", _h_file);
					}
					printf("keyword found -> %s\n", symbol_table->data[i].name);
					fprintf(_h_file, "&%s", symbol_table->data[i].name);
				}
			}
		}
		fputs("}\n\n", _h_file);
		//also generate the header file extern references
		for(int i = 0;i <= symbol_table->size;i++)
		{
			if(symbol_table->data + i)
			{
				if(symbol_table->data[i].scope_type == TYPE_ARG & symbol_table->data[i].type == TYPE_IDENTIFIER)
				{
					fprintf(_h_file, "extern ARG_NODE_TEMPLATE %s;\n", symbol_table->data[i].name);
				}
			}
		}
		//Separate lines on the header file
		fputs("\n", _h_file);
	}
}
/*
   The strcuture that this function should generate

   typedef struct
   {
   ARG_NODE_TEMPLATE* templates;
   int size
   } ARG_TEMPLATE;


   ARG_TEMPLATE domain 

   ARG_TEMPLATE name = { .templates = {
   &A,
   &B,
   &C
   },

   .size = 2; //n -1
   }
   */
void gen_arg_template(SYMBOL_TABLE* symbol_table, FILE* c_file, FILE* h_file)
{
	//all nodes within the scope_type of arg_template are templates
	printf("----------------ARG TEMPLATES----------------\n");
	fputs("/*----------------ARG TEMPLATES----------------*/\n", c_file);
	fputs("/*----------------ARG TEMPLATES----------------*/\n", h_file);
	bool first = true;
	//extract and print all the arg template domains 
	if(symbol_table)
	{
		for(int i = 0;i <= symbol_table->size;i++)
		{
			if(symbol_table->data + i)
			{
				if(symbol_table->data[i].scope_type == TYPE_ARG_TEMPLATE & symbol_table->data[i].type == TYPE_IDENTIFIER)
				{
					printf("keyword found -> %s\n", symbol_table->data[i].name);
					fprintf(c_file, "ARG_TEMPLATE %s = { .templates = {", symbol_table->data[i].name);
					first = true;
					//fpintf all args 
					for(int x = 0; x <= symbol_table->data[i].list->size;x++)
					{
						if(first)
						{
							first = false;
						}
						else
						{
							fputc(',', c_file);
						}
						fprintf(c_file, "\"%s\"", symbol_table->data[i].list->data[x].identifier);
					}
					printf("sizeof %d\n", sizeof(symbol_table->data[i]));
					fprintf(c_file, "}, .size = %d};\n", symbol_table->data[i].list->size);
				}
			}	
		}

		fputs("#define ARG_TEMPLATES {", h_file);
		first = true;
		for(int i = 0;i <= symbol_table->size;i++)
		{
			if(symbol_table->data + i)
			{
				if(symbol_table->data[i].scope_type == TYPE_ARG_TEMPLATE & symbol_table->data[i].type == TYPE_IDENTIFIER)
				{
					if(first) first = false;
					else 
					{
						fputs(", ", h_file);
					}
					printf("keyword found -> %s\n", symbol_table->data[i].name);
					fprintf(h_file, "%s", symbol_table->data[i].name);
				}
			}	
		}

		fputs("}\n\n", h_file);
		fputs("\n", c_file);
	}
}

void gen_ins(SYMBOL_TABLE* symbol_table, FILE* _c_file, FILE* _h_file)
{
	//To know the state if there is need to include another comma
	bool first = true;
	//all nodes within the scope_type of arg_template are templates
	printf("----------------INSTRUCTIONS----------------\n");
	fputs("/*----------------INSTRUCTIONS----------------*/\n", _c_file);
	fputs("/*----------------INSTRUCTIONS----------------*/\n", _h_file);
	//extract and print all the arg template domains 
	if(symbol_table)
	{
		for(int i = 0;i <= symbol_table->size;i++)
		{
			if(symbol_table->data + i)
			{
				if(symbol_table->data[i].scope_type == TYPE_DEF)
				{
					printf("instruction found -> %s\n", symbol_table->data[i].name);
					//INS_NODE_TEMPLATE shftr = {.op = iSHFTR, .name="shftr", .nargs = 3, .relative_args = {0, 0, 0}, .asm_func = &assemble_alu};

					fprintf(_c_file, "INS_NODE_TEMPLATE %s = { .name=\"%s\", .arg_templates = {", \
							symbol_table->data[i].name, symbol_table->data[i].name);
					fprintf(_h_file, "extern INS_NODE_TEMPLATE %s;\n", symbol_table->data[i].name);
					first = true;
					for(int x = 0;x <= symbol_table->size;x++)
					{
						if(symbol_table->data + x)
						{
							if(symbol_table->data[x].scope_type == TYPE_ARG_TEMPLATE & symbol_table->data[x].type == TYPE_IDENTIFIER & (strcmp(symbol_table->data[x].domain, symbol_table->data[i].name) == 0))
							{

								if(first)
								{
									first = false;
								}
								else
								{
									fputs(",", _c_file);
								}
								printf("keyword found -> %s\n", symbol_table->data[x].name);
								printf("\tdomain -> %s\n", symbol_table->data[x].domain);
								fprintf(_c_file, " &%s", symbol_table->data[x].name);
								//fpintf all args 

							}
						}
					}	
					fputs("}, .nargs = 3 /* .relative_args = {0, 0, 0}, .asm_func = &assemble_alu*/};\n", _c_file);
				}
			}
		}

		first = true;

		//Now define the structure that holds all the instruction node pointers
		fputs(INS_TEMPLATE_ARRAY_INFO, _h_file);
		fputs("#define INS_TEMPLATE_ARRAY {", _h_file);
		for(int i = 0;i <= symbol_table->size;i++)
		{
			if(symbol_table->data + i)
			{
				if(symbol_table->data[i].scope_type == TYPE_DEF)
				{
					if(first)
					{
						first = false;
					}
					else
					{
						fputs(", ", _h_file);
					}
					fprintf(_h_file, "&%s", symbol_table->data[i].name);
				}
			}
		}
		fputs("}", _h_file);
	}
}

void gen_ins_templates()
{

}
FILE* c_file;
FILE* c_header;
int main(void)
{
	//Open or create output files
	c_header = fopen (DEFAULT_HEADER_FILE,"w");
	c_file = fopen (DEFAULT_C_FILE,"w");

	if(c_header != NULL & c_file != NULL)
	{
		//Initilize
		init_symbol_table(&symbol_table);
		reset_identifiers();
		yyparse();
		print_symbol_table(&symbol_table);

		fputs(PROLOGUE_H, c_header);
		fputs(PROLOGUE_C, c_file);

		gen_keywords(&symbol_table, c_file, c_header);
		gen_arg_template(&symbol_table, c_file, c_header);
		gen_ins(&symbol_table, c_file, c_header);

		fputs(EPILOUGE_H, c_header);

		fclose(c_file);
		fclose(c_header);
	}
	return 0;
}

