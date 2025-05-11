#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 128
#define MAX_LINES 1000

// Simple opcode simulation for machine code generation
#define LOAD_OP  0x01
#define ADD_OP   0x02
#define SUB_OP   0x03
#define MUL_OP   0x04
#define DIV_OP   0x05
#define STORE_OP 0x06
#define RET_OP   0x07
#define LABEL_OP 0x08

// Function to trim whitespace from the beginning and end of a string
char* trim(char* str) {
    while (isspace(*str)) str++;
    char* end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) *end-- = '\0';
    return str;
}

// Function to generate machine code
void generate_machine_code_line(FILE *out, char* line) {
    char lhs[20], op1[20], op[5], op2[20];

    // Parse binary operation: t1 = a + b
    if (sscanf(line, "%s = %s %s %s", lhs, op1, op, op2) == 4) {
        // Convert to machine code (simplified with opcodes)
        fprintf(out, "LOAD %s -> Opcode: 0x%02X\n", op1, LOAD_OP);
        if (strcmp(op, "+") == 0) fprintf(out, "ADD %s -> Opcode: 0x%02X\n", op2, ADD_OP);
        else if (strcmp(op, "-") == 0) fprintf(out, "SUB %s -> Opcode: 0x%02X\n", op2, SUB_OP);
        else if (strcmp(op, "*") == 0) fprintf(out, "MUL %s -> Opcode: 0x%02X\n", op2, MUL_OP);
        else if (strcmp(op, "/") == 0) fprintf(out, "DIV %s -> Opcode: 0x%02X\n", op2, DIV_OP);
        fprintf(out, "STORE %s -> Opcode: 0x%02X\n", lhs, STORE_OP);
    }

    // Parse simple assignment: x = y
    else if (sscanf(line, "%s = %s", lhs, op1) == 2 && !strstr(line, "return") && !strstr(line, "function")) {
        // Simple assignment to machine code
        fprintf(out, "LOAD %s -> Opcode: 0x%02X\n", op1, LOAD_OP);
        fprintf(out, "STORE %s -> Opcode: 0x%02X\n", lhs, STORE_OP);
    }

    // Parse return statement
    else if (strstr(line, "return") != NULL) {
        sscanf(line, "return %s", op1);
        fprintf(out, "LOAD %s -> Opcode: 0x%02X\n", op1, LOAD_OP);
        fprintf(out, "RET -> Opcode: 0x%02X\n", RET_OP);
    }

    // Parse function label
    else if (strstr(line, "function") != NULL) {
        sscanf(line, "function %s", op1);
        fprintf(out, "LABEL %s -> Opcode: 0x%02X\n", op1, LABEL_OP);
    }
}

int main() {
    FILE *in = fopen("../optimizer/optimized_output.txt", "r");
    FILE *out = fopen("machine_code.txt", "w");

    if (!in || !out) {
        perror("Error opening files");
        return 1;
    }

    char line[MAX_LINE];

    while (fgets(line, sizeof(line), in)) {
        char* clean = trim(line);
        if (strlen(clean) == 0) continue;
        generate_machine_code_line(out, clean);
    }

    fclose(in);
    fclose(out);
    printf("✅ Machine code generation complete. Output written to machine_code.txt\n");
    return 0;
}
