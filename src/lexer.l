%{
#include "tokens.h"
#include "parser.tab.h"
#include <stdio.h>
%}

DIGIT   [0-9]
ID      [a-zA-Z_][a-zA-Z0-9_]*

%%

"int"           { return INT; }
"if"            { return IF; }
"else"          { return ELSE; }
"print"         { return PRINT; }

{ID}            { yylval.str = strdup(yytext); return ID; }
{DIGIT}+        { yylval.num = atoi(yytext); return NUMBER; }

"=="            { return EQ; }
"!="            { return NEQ; }
">="            { return GE; }
"<="            { return LE; }
">"             { return GT; }
"<"             { return LT; }

"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MUL; }
"/"             { return DIV; }

"="             { return ASSIGN; }
";"             { return SEMI; }
"("             { return LPAREN; }
")"             { return RPAREN; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }

[ \t\n]+        ; // Ignore whitespace

.               { printf("Unknown character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}
