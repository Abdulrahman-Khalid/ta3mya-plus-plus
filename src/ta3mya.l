%{
#include "heading.h"
#include "ta3mya.tab.h"

int yyerror(char *s);
extern "C" int yylex(void);

#define STR() yylval.str_val = new std::string(yytext, yyleng)
%}

    // increment yylineno automatically
%option yylineno

digit                   [0-9]
int_literal             {digit}+
real_literal            {digit}+\.{digit}+
rest_chars              .
symbol                  [a-zA-Z0-9_]+
tarqeem_instance        {symbol}::{symbol}
single_cmnt             "//".*
mult_cmnt               "/*"[^*/]*"*/"
whitespace              [ \t]*

%%

    /* ignored */
{single_cmnt} { }
{mult_cmnt}   { }
{whitespace}  { }

\n            { return T_NEWLINE; }

"lw"          { return T_LW; }
"8ero"        { return T_8ERO; }

"lef"         { return T_LEF; }
"l7d"         { return T_L7D; }
"talma"       { return T_TALMA; }
"karrar"      { return T_KARRAR; }

"msh"         { return T_MSH; }
"we"          { STR(); return T_WE; }
"aw"          { STR(); return T_AW; }

"!="          { STR(); return T_DOESNT_EQUAL; }
"=="          { STR(); return T_EQUALS; }
">"           { STR(); return T_GREATER; }
">="          { STR(); return T_GREATER_EQUAL; }
"<"           { STR(); return T_LESS; }
"<="          { STR(); return T_LESS_EQUAL; }

"fe"          { return T_FE; }
"7alet"       { return T_7ALET; }

"thabet"      { return T_THABET; }
"sa7e7"       { STR(); return T_SA7E7; }
"7a2i2i"      { STR(); return T_7A2I2I; }
"tarqeem"     { return T_TARQEEM; }

"="           { return T_ASSIGNMENT; }
"+"           { STR(); return T_PLUS; }
"-"           { STR(); return T_NEG; }
"*"           { STR(); return T_MULT; }
"/"           { STR(); return T_DIV; }
"%"           { STR(); return T_MODULO; }
"**"          { STR(); return T_EXPONENT; }

"basy"        { return T_BASY; }

":"           { return T_COLON; }
";"           { return T_SEMICOLON; }
","           { return T_COMMA; }
"{"           { return T_CRULY_BR_BGN; }
"}"           { return T_CRULY_BR_END; }
"("           { return T_ROUND_BR_BGN; }
")"           { return T_ROUND_BR_END; }

{int_literal}       { STR(); return T_INT_LITERAL; }
{real_literal}      { STR(); return T_REAL_LITERAL; }
{tarqeem_instance}  { STR(); return T_TARQEEM_INSTANCE; }
{symbol}            { STR(); return T_SYMBOL; }

    /* invalid */
{rest_chars} {
    std::cerr << "SCANNER ";
    yyerror("");
    exit(1);
}

%%
