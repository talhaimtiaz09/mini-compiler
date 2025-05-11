#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 100

typedef struct
{
    char *name;     // Name of the variable
    int type;       // Type (0 for int, 1 for string, etc.)
    int is_defined; // Flag to check if variable is defined
} Symbol;

Symbol symbol_table[MAX_SYMBOLS];
int symbol_count = 0;

// Find a symbol in the symbol table
int find_symbol(char *name)
{
    for (int i = 0; i < symbol_count; i++)
    {
        if (strcmp(symbol_table[i].name, name) == 0)
        {
            return i;
        }
    }
    return -1;
}

// Add a new symbol to the table
void add_symbol(char *name, int type)
{
    if (find_symbol(name) != -1)
    {
        printf("Error: Variable '%s' already defined.\n", name);
        exit(1);
    }
    symbol_table[symbol_count].name = strdup(name);
    symbol_table[symbol_count].type = type;
    symbol_table[symbol_count].is_defined = 0;
    symbol_count++;
}

// Mark a symbol as defined
void mark_symbol_defined(char *name)
{
    int index = find_symbol(name);
    if (index == -1)
    {
        printf("Error: Variable '%s' not declared.\n", name);
        exit(1);
    }
    symbol_table[index].is_defined = 1;
}

// Check if a symbol is defined
void check_variable_defined(char *name)
{
    int index = find_symbol(name);
    if (index == -1)
    {
        printf("Error: Variable '%s' not declared.\n", name);
        exit(1);
    }
    if (!symbol_table[index].is_defined)
    {
        printf("Warning: Variable '%s' declared but not defined.\n", name);
    }
}
