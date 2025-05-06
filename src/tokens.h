#ifndef TOKENS_H
#define TOKENS_H

typedef union
{
    int num;
    char *str;
} YYSTYPE;

#define YYSTYPE_IS_DECLARED 1

#endif
