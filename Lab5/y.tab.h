/* A Bison parser, made by GNU Bison 3.7.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TK_ASSIGN = 258,               /* TK_ASSIGN  */
    TK_ADD = 259,                  /* TK_ADD  */
    TK_SUB = 260,                  /* TK_SUB  */
    TK_MUL = 261,                  /* TK_MUL  */
    TK_DIV = 262,                  /* TK_DIV  */
    TK_L = 263,                    /* TK_L  */
    TK_LE = 264,                   /* TK_LE  */
    TK_G = 265,                    /* TK_G  */
    TK_GE = 266,                   /* TK_GE  */
    TK_EQ = 267,                   /* TK_EQ  */
    TK_NE = 268,                   /* TK_NE  */
    TK_D = 269,                    /* TK_D  */
    TK_CHAR_TYPE = 270,            /* TK_CHAR_TYPE  */
    TK_VAR = 271,                  /* TK_VAR  */
    TK_INT = 272,                  /* TK_INT  */
    TK_IF = 273,                   /* TK_IF  */
    TK_EIF = 274,                  /* TK_EIF  */
    TK_WHILE = 275,                /* TK_WHILE  */
    TK_EWHILE = 276,               /* TK_EWHILE  */
    TK_READ = 277,                 /* TK_READ  */
    TK_WRITE = 278,                /* TK_WRITE  */
    TK_SEMC = 279,                 /* TK_SEMC  */
    TK_C = 280,                    /* TK_C  */
    TK_MOD = 281,                  /* TK_MOD  */
    TK_L_B = 282,                  /* TK_L_B  */
    TK_R_B = 283,                  /* TK_R_B  */
    TK_IDENTIFIER = 284,           /* TK_IDENTIFIER  */
    TK_CHAR = 285,                 /* TK_CHAR  */
    TK_NUMBER = 286                /* TK_NUMBER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define TK_ASSIGN 258
#define TK_ADD 259
#define TK_SUB 260
#define TK_MUL 261
#define TK_DIV 262
#define TK_L 263
#define TK_LE 264
#define TK_G 265
#define TK_GE 266
#define TK_EQ 267
#define TK_NE 268
#define TK_D 269
#define TK_CHAR_TYPE 270
#define TK_VAR 271
#define TK_INT 272
#define TK_IF 273
#define TK_EIF 274
#define TK_WHILE 275
#define TK_EWHILE 276
#define TK_READ 277
#define TK_WRITE 278
#define TK_SEMC 279
#define TK_C 280
#define TK_MOD 281
#define TK_L_B 282
#define TK_R_B 283
#define TK_IDENTIFIER 284
#define TK_CHAR 285
#define TK_NUMBER 286

/* Value type.  */


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
