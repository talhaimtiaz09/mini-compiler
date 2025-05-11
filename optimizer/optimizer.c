// optimizer/optimizer.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "optimizer.h"

#define MAX_LINE 128

// Simple constant folding and dead code removal
void optimize_ir(const char *input_file, const char *output_file)
{
    FILE *fin = fopen(input_file, "r");
    FILE *fout = fopen(output_file, "w");
    if (!fin || !fout)
    {
        perror("File error");
        exit(1);
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), fin))
    {
        char dest[32], op1[32], op[4], op2[32];

        if (sscanf(line, "%s = %s %s %s", dest, op1, op, op2) == 4)
        {
            // Constant folding
            int val1, val2;
            if (sscanf(op1, "%d", &val1) && sscanf(op2, "%d", &val2))
            {
                int result;
                if (strcmp(op, "+") == 0)
                    result = val1 + val2;
                else if (strcmp(op, "-") == 0)
                    result = val1 - val2;
                else if (strcmp(op, "*") == 0)
                    result = val1 * val2;
                else if (strcmp(op, "/") == 0)
                    result = val2 != 0 ? val1 / val2 : 0;
                else
                    result = 0;
                fprintf(fout, "%s = %d\n", dest, result);
                continue;
            }
        }
        fputs(line, fout);
    }

    fclose(fin);
    fclose(fout);
}
