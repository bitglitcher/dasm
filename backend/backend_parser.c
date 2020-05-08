#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libs/symbol_table.h"

SYMBOL_TABLE symbol_table;

int main()
{
    init_symbol_table(&symbol_table);

    return 0;
}