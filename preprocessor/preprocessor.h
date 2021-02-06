#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern char* remove_line_comment(char *str, size_t size);
extern char* remove_block_comment(char *str, size_t size);
extern char* remove_gnu_as_comment(char* str, size_t size);