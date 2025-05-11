#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES 1000
#define MAX_LINE_LEN 128

char* trim(char* str) {
    while (isspace(*str)) str++;
    char* end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) *end-- = '\0';
    return str;
}

int isTemporary(const char* var) {
    return var[0] == 't';
}

int isNumber(const char* str) {
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

int main() {
    FILE *in = fopen("../ir_generator/icg_output.txt", "r");
    if (!in) {
        perror("Error opening icg_output.txt");
        return 1;
    }

    char lines[MAX_LINES][MAX_LINE_LEN];
    char output[MAX_LINES][MAX_LINE_LEN];
    int keep[MAX_LINES] = {0};
    char vars[100][20], exprs[100][MAX_LINE_LEN];
    int lineCount = 0, exprCount = 0;

    // Read and clean lines
    while (fgets(lines[lineCount], MAX_LINE_LEN, in)) {
        char* trimmed = trim(lines[lineCount]);

        // Skip USE comments
        if (strncmp(trimmed, "// USE:", 7) == 0) continue;

        strcpy(lines[lineCount], trimmed);
        lineCount++;
    }
    fclose(in);

    // First pass: propagate copies and remove unused temps
    for (int i = 0; i < lineCount; i++) {
        char target[20], src[100];

        // Match simple copy: x = y
        if (sscanf(lines[i], "%s = %s", target, src) == 2 &&
            !strstr(lines[i], "+") &&
            !strstr(lines[i], "-") &&
            !strstr(lines[i], "*") &&
            !strstr(lines[i], "/") &&
            strcmp(target, "return") != 0 &&
            strcmp(target, "function") != 0) {

            int replaced = 0;
            for (int j = 0; j < i; j++) {
                char* pos = strstr(lines[j], target);
                if (pos) {
                    // Replace target with src
                    char temp[MAX_LINE_LEN];
                    strcpy(temp, lines[j]);
                    char* token = strtok(temp, " \n");
                    strcpy(lines[j], "");
                    while (token) {
                        if (strcmp(token, target) == 0)
                            strcat(lines[j], src);
                        else
                            strcat(lines[j], token);
                        strcat(lines[j], " ");
                        token = strtok(NULL, " \n");
                    }
                    replaced = 1;
                }
            }

            if (!replaced) {
                // Save copy for later substitution
                strcpy(vars[exprCount], target);
                strcpy(exprs[exprCount], src);
                exprCount++;
            }

            continue; // Skip adding this assignment
        }

        // Replace known variable copies
        for (int j = 0; j < exprCount; j++) {
            char temp[MAX_LINE_LEN];
            strcpy(temp, lines[i]);
            char* token = strtok(temp, " \n");
            strcpy(lines[i], "");
            while (token) {
                if (strcmp(token, vars[j]) == 0)
                    strcat(lines[i], exprs[j]);
                else
                    strcat(lines[i], token);
                strcat(lines[i], " ");
                token = strtok(NULL, " \n");
            }
        }

        // Keep return and function and useful expressions
        keep[i] = 1;
    }

    // Second pass: eliminate dead temps not used in return
    for (int i = 0; i < lineCount; i++) {
        if (!keep[i]) continue;

        char target[20], rhs[100];
        if (sscanf(lines[i], "%s = %s", target, rhs) == 2 &&
            isTemporary(target) &&
            !strstr(lines[i], "return")) {

            int used = 0;
            for (int j = i + 1; j < lineCount; j++) {
                if (strstr(lines[j], target)) {
                    used = 1;
                    break;
                }
            }

            if (!used) keep[i] = 0;
        }
    }

    // Output final cleaned lines
    FILE *out = fopen("optimized_output.txt", "w");
    if (!out) {
        perror("Error opening optimized_output.txt");
        return 1;
    }

    for (int i = 0; i < lineCount; i++) {
        if (keep[i]) {
            char* trimmed = trim(lines[i]);
            if (strlen(trimmed) > 0)
                fprintf(out, "%s\n", trimmed);
        }
    }

    fclose(out);
    printf("✅ Final optimized output written to optimized_output.txt\n");
    return 0;
}







