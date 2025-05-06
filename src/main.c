#include <stdio.h>
#include "ast.h"

extern int yyparse();
extern Node *root;

int main()
{
    printf("Starting compilation...\n");
    yyparse();
    printf("Abstract Syntax Tree:\n");
    print_ast(root, 0);
    return 0;
}
