%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"
#include "semantic.c"  // Include the semantic analyzer

extern int line_num;   // Line number for error reporting (if needed)
int yylex();           // Declare yylex
%}

%union {
    int num;          // For numbers
    char* str;        // For identifiers and strings
}

%token <str> IDENTIFIER
%token <num> NUMBER
%token DEF RETURN IF ELSE WHILE
%token PLUS MINUS MULT DIV ASSIGN EQ
%token LPAREN RPAREN LBRACE RBRACE COLON COMMA SEMI

%type <num> expression term factor

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
        analyze_return($2);  // Now passing an integer
        printf("Return value: %d\n", $2);
    }
    | IDENTIFIER ASSIGN expression SEMI {
        analyze_assignment($1, $3);  // Passing identifier and integer value
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
        free($1);  // Free the identifier string after use
        $$ = 0; 
    }
    | LPAREN expression RPAREN { $$ = $2; }
;

%%

/* Main function */
int main() {
    printf("Starting parsing...\n");

    // Initialize symbol table (example)
    add_symbol("x", 0);  // Example: Adding symbol 'x'
    add_symbol("y", 0);  // Example: Adding symbol 'y'

    yyparse();  // Start parsing the input
    printf("Parsing complete.\n");

    return 0;
}
