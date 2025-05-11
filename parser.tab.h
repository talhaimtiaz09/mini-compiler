/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     NUMBER = 259,
     DEF = 260,
     RETURN = 261,
     IF = 262,
     ELSE = 263,
     WHILE = 264,
     PLUS = 265,
     MINUS = 266,
     MULT = 267,
     DIV = 268,
     ASSIGN = 269,
     EQ = 270,
     LPAREN = 271,
     RPAREN = 272,
     LBRACE = 273,
     RBRACE = 274,
     COLON = 275,
     COMMA = 276,
     SEMI = 277
   };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define NUMBER 259
#define DEF 260
#define RETURN 261
#define IF 262
#define ELSE 263
#define WHILE 264
#define PLUS 265
#define MINUS 266
#define MULT 267
#define DIV 268
#define ASSIGN 269
#define EQ 270
#define LPAREN 271
#define RPAREN 272
#define LBRACE 273
#define RBRACE 274
#define COLON 275
#define COMMA 276
#define SEMI 277




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 16 "parser/parser.y"
{
    int num;          // For numbers
    char* str;        // For identifiers and strings
}
/* Line 1529 of yacc.c.  */
#line 98 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

