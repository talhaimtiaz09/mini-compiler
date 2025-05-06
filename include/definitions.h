// include/definitions.h

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max length of an identifier
#define MAX_ID_LEN 32

// Structures for AST, symbol table, etc.
typedef struct ast_node
{
    int type;
    char value[MAX_ID_LEN];
    struct ast_node *left, *right;
} ASTNode;

typedef struct symbol
{
    char name[MAX_ID_LEN];
    int type;
    struct symbol *next;
} Symbol;

extern FILE *output_file; // File for generating code or output

// Function prototypes
void print_ast(ASTNode *root);
void print_symbol_table(Symbol *table);

#endif // DEFINITIONS_H
