#ifndef AST_H
#define AST_H

typedef struct Node
{
    char *type;
    char *value; // for ID or number
    struct Node *left;
    struct Node *right;
} Node;

Node *create_node(const char *type, Node *left, Node *right);
Node *create_leaf(const char *val);
Node *create_leaf_int(int val);
void print_ast(Node *root, int level);

#endif
