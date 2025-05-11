%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.tab.h"

int yylex();
void yyerror(const char *s);

extern int line_num;
%}

%union {
    int num;
    char* str;  // For identifiers and expressions
}

%token <str> IDENTIFIER
%token <num> NUMBER
%token DEF RETURN IF ELSE WHILE
%token PLUS MINUS MULT DIV ASSIGN EQ
%token LPAREN RPAREN LBRACE RBRACE COLON COMMA SEMI

%type <str> expression term factor

%%

program:
    function_list
;

function_list:
    function_list function
    | function
;

function:
    DEF IDENTIFIER LPAREN param_list RPAREN COLON statement_block
    {
        printf("DECL function %s\n", $2);
        free($2);
    }
;

param_list:
    IDENTIFIER COMMA param_list
    | IDENTIFIER
    | /* empty */
;

statement_block:
    LBRACE statement_list RBRACE
;

statement_list:
    statement_list statement
    | statement
;

statement:
    RETURN expression SEMI {
        printf("RETURN value: %s\n", $2);
        free($2);
    }
    | IDENTIFIER ASSIGN expression SEMI {
        printf("ASSIGN %s %s\n", $1, $3);
        free($1); free($3);
    }
    | IF expression COLON statement_block
    | WHILE expression COLON statement_block
;

expression:
    expression PLUS term {
        $$ = malloc(strlen($1) + strlen($3) + 4);
        sprintf($$, "%s + %s", $1, $3);
        free($1); free($3);
    }
    | expression MINUS term {
        $$ = malloc(strlen($1) + strlen($3) + 4);
        sprintf($$, "%s - %s", $1, $3);
        free($1); free($3);
    }
    | term {
        $$ = $1;
    }
;

term:
    term MULT factor {
        $$ = malloc(strlen($1) + strlen($3) + 4);
        sprintf($$, "%s * %s", $1, $3);
        free($1); free($3);
    }
    | term DIV factor {
        $$ = malloc(strlen($1) + strlen($3) + 4);
        sprintf($$, "%s / %s", $1, $3);
        free($1); free($3);
    }
    | factor {
        $$ = $1;
    }
;

factor:
    NUMBER {
        $$ = malloc(20);
        sprintf($$, "%d", $1);
    }
    | IDENTIFIER {
        printf("USE variable '%s'\n", $1);
        $$ = strdup($1);
        free($1);
    }
    | LPAREN expression RPAREN {
        $$ = malloc(strlen($2) + 3);
        sprintf($$, "(%s)", $2);
        free($2);
    }
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error: %s\n", s);
}

int main() {
    printf("Starting parsing...\n");
    yyparse();
    printf("Parsing complete.\n");
    return 0;
}


