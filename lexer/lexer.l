%{
#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

#ifdef PARSER
#include "parser.tab.h"
extern YYSTYPE yylval;
#endif

int line_num = 1;

const char* token_name(int token) {
    switch (token) {
        case IF: return "IF";
        case ELSE: return "ELSE";
        case WHILE: return "WHILE";
        case DEF: return "DEF";
        case RETURN: return "RETURN";
        case IDENTIFIER: return "IDENTIFIER";
        case NUMBER: return "NUMBER";
        case ASSIGN: return "ASSIGN";
        case EQ: return "EQ";
        case LPAREN: return "LPAREN";
        case RPAREN: return "RPAREN";
        case LBRACE: return "LBRACE";
        case RBRACE: return "RBRACE";
        case SEMI: return "SEMI";
        case COLON: return "COLON";
        case COMMA: return "COMMA";
        case PLUS: return "PLUS";
        case MINUS: return "MINUS";
        case MULT: return "MULT";
        case DIV: return "DIV";
        default: return "UNKNOWN";
    }
}

%}

DIGIT      [0-9]
ID         [a-zA-Z_][a-zA-Z0-9_]*
WS         [ \t]+

%%

"if"        { return IF; }
"else"      { return ELSE; }
"while"     { return WHILE; }
"def"       { return DEF; }
"return"    { return RETURN; }

{ID} {
#ifdef PARSER
    yylval.str = strdup(yytext); // Save identifier value if parser is active
#endif
    return IDENTIFIER;
}

{DIGIT}+ {
#ifdef PARSER
    yylval.num = atoi(yytext); // Save number value if parser is active
#endif
    return NUMBER;
}

"="         { return ASSIGN; }
"=="        { return EQ; }
"("         { return LPAREN; }
")"         { return RPAREN; }
"{"         { return LBRACE; }
"}"         { return RBRACE; }
";"         { return SEMI; }
":"         { return COLON; }
","         { return COMMA; }
"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return MULT; }
"/"         { return DIV; }

{WS}        { /* skip whitespace */ }
\n          { line_num++; }
.           { printf("Unknown character: %s\n", yytext); }

%%

#ifndef PARSER
int main() {
    int tok;
    while ((tok = yylex())) {
        printf("Token: %s, Value: %s\n", token_name(tok), yytext); // Print token and its value
    }
    return 0;
}

#endif
