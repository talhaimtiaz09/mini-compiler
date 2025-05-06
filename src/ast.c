#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

Node *create_node(const char *type, Node *left, Node *right)
{
    Node *node = malloc(sizeof(Node));
    node->type = strdup(type);
    node->value = NULL;
    node->left = left;
    node->right = right;
    return node;
}

Node *create_leaf(const char *val)
{
    Node *node = malloc(sizeof(Node));
    node->type = strdup("id");
    node->value = strdup(val);
    node->left = node->right = NULL;
    return node;
}

Node *create_leaf_int(int val)
{
    Node *node = malloc(sizeof(Node));
    node->type = strdup("num");
    node->value = malloc(20);
    sprintf(node->value, "%d", val);
    node->left = node->right = NULL;
    return node;
}

void print_ast(Node *root, int level)
{
    if (!root)
        return;
    for (int i = 0; i < level; i++)
        printf("  ");
    printf("[%s", root->type);
    if (root->value)
        printf(": %s", root->value);
    printf("]\n");
    print_ast(root->left, level + 1);
    print_ast(root->right, level + 1);
}
