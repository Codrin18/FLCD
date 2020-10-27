%option noyywrap

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "symtab.c"
    #include "pif.c"

    extern FILE *yyin;
    extern FILE *yyout;

    int lineno = 1; // initialize to 1
    int pozID = 0;
    void ret_print(char *token_type);
    void yyerror();
%}

%x ML_COMMENT

alphabet [a-zA-Z]
digit [0-9]
num {alphabet}|{digit}
print [ -~]

ID {alphabet}+{num}*
INTCONST "0"|[0-9]{digit}*
RCONST "0"|{digit}*"."{digit}+
CHARCONST (\'{print}\')|(\'\\[nftrbv]\')
STRING \"{print}*\" 

%%

"//".*                  { printf("Eat up comment at line %d\n", lineno); } 

"/*"                    { printf("Eat up comment from line %d ", lineno); BEGIN(ML_COMMENT); }
<ML_COMMENT>"*/"        { printf("to line %d\n", lineno); BEGIN(INITIAL); }
<ML_COMMENT>[^*\n]+     
<ML_COMMENT>"*"         
<ML_COMMENT>"\n"        { lineno += 1; }

"INT" { ret_print("KEYWORD_INT");}
"BOOL" { ret_print("KEYWORD_BOOL");}
"CHAR" { ret_print("KEYWORD_CHAR");}
"IF" { ret_print("KEYWORD_IF");}
"ELSE" {ret_print("KEYWORD_ELSE");}
"END-IF" {ret_print("KEYWORD_ENDIF");}
"WHILE" {ret_print("KEYWORD_WHILE");}
"END-WHILE" {ret_print("KEYWORD_ENDWHILE");}
"LIST" {ret_print("KEYWORD_LIST");}
"READ" {ret_print("KEYWORD_READ");}
"WRITE" {ret_print("KEYWORD_WRITE");}
"VAR" {ret_print("KEYWORD_VAR");}

"+"|"-" {ret_print("ADDOP");}
"*" {ret_print("MULOP");}
"/" {ret_print("DIVOP");}
"=="|"!=" {ret_print("EQOP");}
">"|"<"|">="|"<=" {ret_print("RELOP");}

"(" { ret_print("LPAREN");}
")" {ret_print("RPAREN");}
";" {ret_print("SEMI");}
":" {ret_print("DPOINT");}
"=" {ret_print("ASSIGN");}
"," {ret_print("COMMA");}

{ID}            { 
                    // insert identifier into symbol table
                    insert(yytext, strlen(yytext), UNDEF, lineno);
                    addIdentifier(yytext, pozID);
                    
                    ret_print("ID");
                }
{INTCONST}        { ret_print("INTCONST"); }
{RCONST}        { ret_print("RCONST"); }
{CHARCONST}        { ret_print("CCONST"); }
{STRING}        { ret_print("STRING"); }

"\n" {lineno += 1;}
[ \t\r\f]+ 

. { yyerror("Unrecognized character");}

%%

void ret_print(char *token_type){
    printf("yytext: %s\ttoken: %s\tlineno %d\n", yytext, token_type, lineno);
}

void yyerror(char *message){
    printf("Error: \"%s\" in line %d. Token = %s\n", message, lineno, yytext);
    exit(1);
}

int main(int argc, char *argv[]){

    init_hash_table();

    yyin = fopen(argv[1], "r");
    yylex();
    fclose(yyin);

    yyout = fopen("symtab_dump.out", "w");
	symtab_dump(yyout);
	fclose(yyout);

    yyout = fopen("pif_dumb.out", "w");
    pif_dumb(yyout);
    fclose(yyout);	

    return 0;
}