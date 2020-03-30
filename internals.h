#include "libs/arg_table.h"


//number handdling
void set_values(int);





typedef struct
{
    int op; //Instruction op
    int nargs; //Number of arguments
    int* relative_arg; //array of 0 or 1 to set relative arguments
} ins_node_template;


typedef struct
{

} ins_node;