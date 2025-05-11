#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.c" // Include symbol table management functions

extern int line_num; // Line number for error reporting (if needed)

void yyerror(const char *s)
{
    fprintf(stderr, "Syntax error: %s\n", s);
}

// Function to analyze expressions
void analyze_expression(char *identifier)
{
    check_variable_defined(identifier); // Check if the variable is defined
}

// Function to analyze assignments
void analyze_assignment(char *var, char *value)
{
    check_variable_defined(value); // Check if the value is defined
    mark_symbol_defined(var);      // Mark the variable as defined after assignment
}

// Function to analyze function return statements
void analyze_return(char *identifier)
{
    check_variable_defined(identifier); // Check if the return value is valid
    printf("Return value for '%s' is valid.\n", identifier);
}
