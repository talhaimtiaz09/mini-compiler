#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct Symbol {
    char* name;
    char* type;  // "int", "str", or "function"
    int declared;  // 1 if declared, 0 if not
    struct Symbol* next;
} Symbol;

// Function declarations for symbol table operations
Symbol* createSymbol(char* name, char* type);
void insertSymbol(Symbol* symbol);
Symbol* lookupSymbol(char* name);
void printSymbolTable();

#endif

