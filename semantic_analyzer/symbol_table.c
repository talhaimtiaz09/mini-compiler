#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

Symbol* symbolTable = NULL;

// Create a new symbol with a given name and type
Symbol* createSymbol(char* name, char* type) {
    Symbol* symbol = (Symbol*)malloc(sizeof(Symbol));
    symbol->name = strdup(name);
    symbol->type = strdup(type);
    symbol->declared = 0;
    symbol->next = NULL;
    return symbol;
}

// Insert a symbol into the symbol table
void insertSymbol(Symbol* symbol) {
    symbol->next = symbolTable;
    symbolTable = symbol;
}

// Lookup a symbol by its name
Symbol* lookupSymbol(char* name) {
    Symbol* current = symbolTable;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Print the symbol table (for debugging purposes)
void printSymbolTable() {
    printf("Symbol Table:\n");
    Symbol* current = symbolTable;
    while (current != NULL) {
        printf("Name: %s, Type: %s, Declared: %d\n", current->name, current->type, current->declared);
        current = current->next;
    }
}

