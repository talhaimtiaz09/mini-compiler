// ir_generator/intermediate.c
#include "intermediate.h"
#include <stdlib.h>
#include <string.h>

static IR *head = NULL;
static IR *tail = NULL;

void generate_ir(const char *op, const char *arg1, const char *arg2, const char *result)
{
    IR *instr = (IR *)malloc(sizeof(IR));
    if (strcmp(op, "+") == 0)
        instr->type = IR_ADD;
    else if (strcmp(op, "-") == 0)
        instr->type = IR_SUB;
    else if (strcmp(op, "*") == 0)
        instr->type = IR_MUL;
    else if (strcmp(op, "/") == 0)
        instr->type = IR_DIV;
    else if (strcmp(op, "=") == 0)
        instr->type = IR_ASSIGN;
    else
        instr->type = IR_LABEL;

    strcpy(instr->arg1, arg1 ? arg1 : "");
    strcpy(instr->arg2, arg2 ? arg2 : "");
    strcpy(instr->result, result ? result : "");
    instr->next = NULL;

    if (head == NULL)
    {
        head = tail = instr;
    }
    else
    {
        tail->next = instr;
        tail = instr;
    }
}

void print_ir_to_file(const char *filename)
{
    FILE *fp = fopen(filename, "w");
    IR *curr = head;
    while (curr)
    {
        switch (curr->type)
        {
        case IR_ADD:
            fprintf(fp, "%s = %s + %s\n", curr->result, curr->arg1, curr->arg2);
            break;
        case IR_SUB:
            fprintf(fp, "%s = %s - %s\n", curr->result, curr->arg1, curr->arg2);
            break;
        case IR_MUL:
            fprintf(fp, "%s = %s * %s\n", curr->result, curr->arg1, curr->arg2);
            break;
        case IR_DIV:
            fprintf(fp, "%s = %s / %s\n", curr->result, curr->arg1, curr->arg2);
            break;
        case IR_ASSIGN:
            fprintf(fp, "%s = %s\n", curr->result, curr->arg1);
            break;
        case IR_LABEL:
            fprintf(fp, "%s:\n", curr->label);
            break;
        default:
            fprintf(fp, "; Unknown instruction\n");
        }
        curr = curr->next;
    }
    fclose(fp);
}

void free_ir_list()
{
    IR *curr = head;
    while (curr)
    {
        IR *tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    head = tail = NULL;
}
