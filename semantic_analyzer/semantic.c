#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"
#include <ctype.h>

// Function to check if a variable is declared before use
void checkDeclaration(char* name) {
    Symbol* symbol = lookupSymbol(name);
    if (symbol == NULL) {
        printf("Error: Variable '%s' used before declaration\n", name);
    } else if (!symbol->declared) {
        printf("Error: Variable '%s' used before assignment\n", name);
    }
}

// Function to declare a variable
void declareVariable(char* name, char* type) {
    Symbol* symbol = lookupSymbol(name);
    if (symbol == NULL) {
        symbol = createSymbol(name, type);
        insertSymbol(symbol);
    }
    symbol->declared = 1;  // Mark the symbol as declared
}

// Function to handle parsed lines (DECL, ASSIGN, USE)
void processLine(char* line) {
    char cmd[20], arg1[50], arg2[50];
    
    if (sscanf(line, "%s %s %s", cmd, arg1, arg2) < 2) return;

    if (strcmp(cmd, "DECL") == 0) {
        // Declare a new variable
        declareVariable(arg2, arg1);
    } else if (strcmp(cmd, "ASSIGN") == 0) {
        // Check if the variable is declared before assignment
        checkDeclaration(arg1);
        declareVariable(arg1, "int");  // Assuming "int" for simplicity
    } else if (strcmp(cmd, "RETURN") == 0) {
        // Check for return values (if the value is an identifier)
        if (isalpha(arg1[0])) {
            checkDeclaration(arg1);
        }
    } else if (strcmp(cmd, "USE") == 0) {
        // Check if the variable is used
        checkDeclaration(arg1);
    }
}

// Main function to process the parsed output file
int main() {
    FILE* f = fopen("tokens.txt", "r");
    if (!f) {
        perror("Error opening parsed output file");
        return 1;
    }

    char line[100];
    while (fgets(line, sizeof(line), f)) {
        processLine(line);
    }

    fclose(f);

    // Print the final symbol table (for debugging purposes)
    printSymbolTable();
    return 0;
}

