#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"

FILE *out;

void emit(Node *root, int indent);

void indent(int level)
{
    for (int i = 0; i < level; i++)
        fprintf(out, "    ");
}

void emit(Node *root, int indent_level)
{
    if (!root)
        return;

    if (strcmp(root->type, "stmt_list") == 0)
    {
        emit(root->left, indent_level);
        emit(root->right, indent_level);
    }
    else if (strcmp(root->type, "decl") == 0 || strcmp(root->type, "assign") == 0)
    {
        indent(indent_level);
        fprintf(out, "%s = ", root->left->value);
        emit(root->right, 0);
        fprintf(out, "\n");
    }
    else if (strcmp(root->type, "print") == 0)
    {
        indent(indent_level);
        fprintf(out, "print(");
        emit(root->left, 0);
        fprintf(out, ")\n");
    }
    else if (strcmp(root->type, "if") == 0)
    {
        indent(indent_level);
        fprintf(out, "if ");
        emit(root->left, 0);
        fprintf(out, ":\n");
        emit(root->right, indent_level + 1);
    }
    else if (strcmp(root->type, "add") == 0 || strcmp(root->type, "sub") == 0 ||
             strcmp(root->type, "mul") == 0 || strcmp(root->type, "div") == 0 ||
             strcmp(root->type, "gt") == 0 || strcmp(root->type, "lt") == 0)
    {
        fprintf(out, "(");
        emit(root->left, 0);
        if (strcmp(root->type, "add") == 0)
            fprintf(out, " + ");
        if (strcmp(root->type, "sub") == 0)
            fprintf(out, " - ");
        if (strcmp(root->type, "mul") == 0)
            fprintf(out, " * ");
        if (strcmp(root->type, "div") == 0)
            fprintf(out, " / ");
        if (strcmp(root->type, "gt") == 0)
            fprintf(out, " > ");
        if (strcmp(root->type, "lt") == 0)
            fprintf(out, " < ");
        emit(root->right, 0);
        fprintf(out, ")");
    }
    else if (strcmp(root->type, "id") == 0 || strcmp(root->type, "num") == 0)
    {
        fprintf(out, "%s", root->value);
    }
}

void generate_python_code(Node *root)
{
    out = fopen("output/generated_code.py", "w");
    if (!out)
    {
        perror("Failed to open output file");
        exit(1);
    }
    emit(root, 0);
    fclose(out);
    printf("Python code generated in output/generated_code.py\n");
}
