// codegen/codegen.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"

// Simple stack machine assembly output
void generate_machine_code(const char *ir_file, const char *output_file)
{
    FILE *fin = fopen(ir_file, "r");
    FILE *fout = fopen(output_file, "w");
    if (!fin || !fout)
    {
        perror("File error");
        exit(1);
    }

    char line[128];
    while (fgets(line, sizeof(line), fin))
    {
        char dest[32], arg1[32], op[4], arg2[32];

        if (sscanf(line, "%s = %s %s %s", dest, arg1, op, arg2) == 4)
        {
            fprintf(fout, "LOAD %s\n", arg1);
            if (strcmp(op, "+") == 0)
                fprintf(fout, "ADD %s\n", arg2);
            else if (strcmp(op, "-") == 0)
                fprintf(fout, "SUB %s\n", arg2);
            else if (strcmp(op, "*") == 0)
                fprintf(fout, "MUL %s\n", arg2);
            else if (strcmp(op, "/") == 0)
                fprintf(fout, "DIV %s\n", arg2);
            fprintf(fout, "STORE %s\n", dest);
        }
        else if (sscanf(line, "%s = %s", dest, arg1) == 2)
        {
            fprintf(fout, "LOAD %s\n", arg1);
            fprintf(fout, "STORE %s\n", dest);
        }
    }

    fclose(fin);
    fclose(fout);
}
