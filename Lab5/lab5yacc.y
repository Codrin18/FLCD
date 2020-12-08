%{

#include <cstdio>
#include <iostream>
using namespace std;

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE* yyin;

void yyerror(const char* s);
%}

%token TK_ASSIGN
%token TK_ADD
%token TK_SUB
%token TK_MUL
%token TK_DIV
%token TK_L 
%token TK_LE
%token TK_G 
%token TK_GE
%token TK_EQ
%token TK_NE
%token TK_D 
%token TK_CHAR_TYPE
%token TK_VAR
%token TK_INT
%token TK_IF
%token TK_EIF
%token TK_WHILE
%token TK_EWHILE
%token TK_READ
%token TK_WRITE
%token TK_SEMC
%token TK_C 
%token TK_MOD
%token TK_L_B 
%token TK_R_B

%token TK_IDENTIFIER
%token <char_t> TK_CHAR
%token <number_t> TK_NUMBER

%%

program:
    TK_VAR decl_list
    ;
decl_list:
    |decl_list declaration
    ;
declaration:
    type TK_D list_identifier 
    ;
list_identifier:
    TK_IDENTIFIER | TK_IDENTIFIER TK_C list_identifier
    ;
type:
    TK_INT;
IF:
    TK_IF expression boolean_operator expression TK_D statement_list TK_EIF { cout << "IF" << endl }
    ;
WHILE:
    TK_WHILE expression boolean_operator expression TK_D statement_list TK_EWHILE { cout << "WHILE" << endl }
    ;
boolean_operator:
    TK_L | TK_LE | TK_G | TK_GE | TK_EQ | TK_NE;
statement_list:
    |statement_list statement 
    ;
statement:
    simple_statement
    ;
simple_statement:
    assign_statement | iostatement
    ;
assign_statement:
    TK_IDENTIFIER TK_ASSIGN expression
    ;
expression:
    expression TK_ADD term | expression TK_SUB term | expression TK_MUL term | expression TK_DIV term | expression TK_MOD term | term 
    ;
term:
    term TK_ADD factor | term TK_SUB factor | term TK_MUL factor | term TK_DIV factor | term TK_MOD factor | factor
    ;
factor:
    TK_L_B expression TK_R_B | TK_IDENTIFIER
    ;
iostatement:
    TK_READ TK_L_B TK_IDENTIFIER TK_R_B | TK_WRITE TK_L_B TK_IDENTIFIER TK_R_B
    ;
%%

int main() {
	FILE *myfile = fopen("source.txt", "r");
	if (!myfile) {
		cout << "can't open file" << endl;
		return -1;
	}

	yyin = myfile;

	do {
		yyparse();
	} while(!feof(yyin));
	return 0;
}


