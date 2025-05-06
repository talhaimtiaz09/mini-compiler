%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "codegen.h"

extern int yylex();
extern int yyparse();
void yyerror(const char *s);

Node* root;
%}

%union {
    int num;
    char* str;
    Node* node;
}

%token <num> NUMBER
%token <str> ID
%token INT IF ELSE PRINT
%token EQ NEQ GE LE GT LT
%token PLUS MINUS MUL DIV ASSIGN SEMI LPAREN RPAREN LBRACE RBRACE

%type <node> stmt expr stmt_list

%%

program:
    stmt_list {
        root = $1;
        generate_python_code(root);
    }
;

stmt_list:
    stmt stmt_list { $$ = create_node("stmt_list", $1, $2); }
    | stmt         { $$ = create_node("stmt_list", $1, NULL); }
;

stmt:
    INT ID ASSIGN expr SEMI {
        $$ = create_node("decl", create_leaf($2), $4);
    }
    | ID ASSIGN expr SEMI {
        $$ = create_node("assign", create_leaf($1), $3);
    }
    | PRINT expr SEMI {
        $$ = create_node("print", $2, NULL);
    }
    | IF LPAREN expr RPAREN LBRACE stmt_list RBRACE {
        $$ = create_node("if", $3, $6);
    }
;

expr:
    expr PLUS expr  { $$ = create_node("add", $1, $3); }
    | expr MINUS expr { $$ = create_node("sub", $1, $3); }
    | expr MUL expr { $$ = create_node("mul", $1, $3); }
    | expr DIV expr { $$ = create_node("div", $1, $3); }
    | expr GT expr  { $$ = create_node("gt", $1, $3); }
    | expr LT expr  { $$ = create_node("lt", $1, $3); }
    | NUMBER        { $$ = create_leaf_int($1); }
    | ID            { $$ = create_leaf($1); }
    | LPAREN expr RPAREN { $$ = $2; }
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parser error: %s\n", s);
}
