%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include header file from Bison to get the token definitions
#include "parser.tab.h"

int yylex();
void yyerror(const char *s);

extern int line_num;
%}

/* Define YYSTYPE union for semantic values */
%union {
    int num;          // For numbers
    char* str;        // For identifiers and strings
}

/* Declare token types and their values */
%token <str> IDENTIFIER
%token <num> NUMBER
%token DEF RETURN IF ELSE WHILE
%token PLUS MINUS MULT DIV ASSIGN EQ
%token LPAREN RPAREN LBRACE RBRACE COLON COMMA SEMI

/* Declare non-terminal types */
%type <num> expression term factor

%%

/* Grammar rules */

program:
    function_list
;

function_list:
    function_list function
    | function
;

function:
    DEF IDENTIFIER LPAREN param_list RPAREN COLON statement_block
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
        printf("Return value: %d\n", $2);
    }
    | IDENTIFIER ASSIGN expression SEMI {
        // Variable assignments not stored in this simple version
        printf("Assignment to variable '%s' = %d\n", $1, $3);
        free($1);
    }
    | IF expression COLON statement_block
    | WHILE expression COLON statement_block
;

expression:
    expression PLUS term { $$ = $1 + $3; }
    | expression MINUS term { $$ = $1 - $3; }
    | term { $$ = $1; }
;

term:
    term MULT factor { $$ = $1 * $3; }
    | term DIV factor { 
        if ($3 == 0) {
            yyerror("Division by zero");
            $$ = 0;
        } else {
            $$ = $1 / $3;
        }
    }
    | factor { $$ = $1; }
;

factor:
    NUMBER { $$ = $1; }
    | IDENTIFIER { 
        printf("Warning: variable '%s' not defined, returning 0\n", $1);
        free($1);
        $$ = 0; 
    }
    | LPAREN expression RPAREN { $$ = $2; }
;

%%

/* Error handling function */
void yyerror(const char *s) {
    fprintf(stderr, "Syntax error: %s\n", s);
}

/* Main function */
int main() {
    printf("Starting parsing...\n");
    yyparse();  // Start parsing the input
    printf("Parsing complete.\n");
    return 0;
}
