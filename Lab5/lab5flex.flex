%option noyywrap

TK_IDENTIFIER [a-zA-Z][a-zA-z0-9_]*
TK_NUMBER ([-\+]{0,1}[1-9][0-9]*)|0
TK_CHAR '[0-9a-zA-Z]'

%{
#include <stdio.h>
#include <iostream>

using namespace std;

#define YY_DECL extern "C" int yylex()

%}

%%

[ \t\n]+ ;
"=" { return TK_ASSIGN; }
"+" {return TK_ADD; }
"-" {return TK_SUB;}
"*" {return TK_MUL;}
"/" {return TK_DIV; }
"<" {return TK_L;}
"<=" {return TK_LE;}
">" {return TK_G;}
">=" {return TK_GE;}
"==" { return TK_EQ; }
"!=" { return TK_NE; }
":" {return TK_D; }
"," {return TK_C; }
";" { return TK_SEMC; }
"%" {return TK_MOD; }
"VAR" {return TK_VAR;}
"CHAR" { return TK_CHAR_TYPE; }
"INT" { return TK_INT; }
"IF" { return TK_IF; }
"END-IF" { return TK_EIF; }
"WHILE" { return TK_WHILE; } 
"END-WHILE" { return TK_EWHILE; }
"READ" { return TK_READ; }
"WRITE" { return TK_WRITE; }
"(" { return TK_L_B; }
")" { return TK_R_B; }

{TK_IDENTIFIER} {return TK_IDENTIFIER;}
{TK_NUMBER} { return TK_NUMBER; }
{TK_CHAR} {return TK_CHAR;}

. { printf("error %s ", yytext); }

%%