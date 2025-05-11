// ir_generator/intermediate.h
#ifndef INTERMEDIATE_H
#define INTERMEDIATE_H

#include <stdio.h>

typedef enum
{
    IR_ADD,
    IR_SUB,
    IR_MUL,
    IR_DIV,
    IR_ASSIGN,
    IR_LABEL,
    IR_GOTO,
    IR_IFGOTO,
    IR_PARAM,
    IR_CALL,
    IR_RETURN
} IRType;

typedef struct IR
{
    IRType type;
    char arg1[32];
    char arg2[32];
    char result[32];
    char label[32];
    struct IR *next;
} IR;

void generate_ir(const char *op, const char *arg1, const char *arg2, const char *result);
void print_ir_to_file(const char *filename);
void free_ir_list();

#endif
