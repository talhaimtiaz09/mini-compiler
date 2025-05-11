#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "icg_utils.h"

void processTokenLine(const char* line) {
    char token[50], value[50];
    if (sscanf(line, "%s %s", token, value) < 2) return;

    static char lastId[50], lastOp[10];
    static int expect = 0; // 0=lhs, 1=assign, 2=rhs or op

    if (strcmp(token, "IDENTIFIER") == 0 || strcmp(token, "NUMBER") == 0) {
        if (expect == 0) {
            strcpy(lastId, value);
            expect = 1;
        } else if (expect == 2) {
            const char* temp = newTemp();
            generateBinaryOp((char*)temp, lastId, lastOp, value);
            strcpy(lastId, temp);  // Result becomes next left operand
            expect = 2;  // More ops could follow
        }
    } else if (strcmp(token, "ASSIGN") == 0) {
        expect = 2;
    } else if (strcmp(token, "PLUS") == 0 || strcmp(token, "MINUS") == 0 ||
               strcmp(token, "MULT") == 0 || strcmp(token, "DIV") == 0) {
        strcpy(lastOp, value);  // like "+" or "*"
        expect = 2;
    } else if (strcmp(token, "SEMI") == 0) {
        generateAssignment(lastId, lastId);  // final assignment
        expect = 0;
    }
}

int tempVarCount = 1;  // To track temporary variable names like t1, t2, etc.

const char* newTemp() {
    static char temp[10];
    sprintf(temp, "t%d", tempVarCount++);
    return temp;
}

void generateICG(const char *line, FILE *out) {
    char keyword[20], arg1[50], arg2[50], op[5], arg3[50];

    printf("%s\n",line);
    // Handling assignment with expression: e.g. ASSIGN c a + b
    if (sscanf(line, "ASSIGN %s %s %s %s", arg1, arg2, op, arg3) == 4) {
        const char* temp = newTemp(); // Generate a temporary variable
        fprintf(out, "%s = %s %s %s\n", temp, arg2, op, arg3); // e.g., t1 = a + b
        fprintf(out, "%s = %s\n", arg1, temp); // e.g., c = t1
    }
    // Handling simple assignment: e.g. ASSIGN c 0
    else if (sscanf(line, "ASSIGN %s %s", arg1, arg2) == 2) {
        fprintf(out, "%s = %s\n", arg1, arg2); // e.g., c = 0
    }
    else if (sscanf(line, "RETURN value: %s", arg1) == 1) {
        fprintf(out, "return %s\n", arg1); // e.g., return 0
    }
    else if (sscanf(line, "DECL function %s", arg1) == 1) {
        fprintf(out, "\nfunction %s:\n", arg1); // Function declaration
    }
    else if (strstr(line, "Starting parsing") || strstr(line, "Parsing complete")) {
        // Ignore these lines
    }
    else if (sscanf(line, "USE variable '%[^']'", arg1) == 1) {
        // For the USE variable, we just note the usage but do not generate code
        // This can be used later for things like symbol table management
        fprintf(out, "// USE: %s\n", arg1); // Just for tracking purposes
    }
    else {
        fprintf(out, "// Unrecognized: %s", line); // For unrecognized lines
    }
}

int main() {
    FILE *in = fopen("../parser/tokens.txt", "r");

    if (!in) {
        perror("Error opening tokens.txt");
        return 1;
    }

    //initICGOutput();
    FILE *out = fopen("icg_output.txt", "w");
    if (!out) {
        perror("Error opening ICG output file");
        return 1;
    }

    char line[128];
    while (fgets(line, sizeof(line), in)) {
        generateICG(line, out);
    }

    //closeICGOutput();
    fclose(out);
    fclose(in);
    printf("Intermediate Code Generation complete. Output written to icg_output.txt\n");
    return 0;
}

