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

int main() {
    FILE *in = fopen("../parser/tokens.txt", "r");

    if (!in) {
        perror("Error opening tokens.txt");
        return 1;
    }

    initICGOutput();

    char line[128];
    while (fgets(line, sizeof(line), in)) {
        processTokenLine(line);
    }

    closeICGOutput();
    fclose(in);
    return 0;
}
