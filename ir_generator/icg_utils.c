#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "icg_utils.h"

static FILE* out = NULL;
static int tempVarCount = 0;

void initICGOutput() {
    out = fopen("icg_output.txt", "w");
    if (!out) {
        perror("Could not open icg_output.txt");
        exit(1);
    }
}

void closeICGOutput() {
    if (out) fclose(out);
}



void generateAssignment(const char* lhs, const char* rhs) {
    fprintf(out, "%s = %s\n", lhs, rhs);
}

void generateBinaryOp(const char* result, const char* arg1, const char* op, const char* arg2) {
    fprintf(out, "%s = %s %s %s\n", result, arg1, op, arg2);
}
