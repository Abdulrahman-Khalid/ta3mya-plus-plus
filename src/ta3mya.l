%{
#include "heading.h"
#include "ta3mya.tab.h"

int yyerror(char *s);
extern "C" int yylex(void);

#define RETURN_STR(t) do { yylval.str_val = new std::string(yytext, yyleng); return (t); } while(0)
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
"we"          { RETURN_STR(T_WE); }
"aw"          { RETURN_STR(T_AW); }

"!="          { RETURN_STR(T_DOESNT_EQUAL); }
"=="          { RETURN_STR(T_EQUALS); }
">"           { RETURN_STR(T_GREATER); }
">="          { RETURN_STR(T_GREATER_EQUAL); }
"<"           { RETURN_STR(T_LESS); }
"<="          { RETURN_STR(T_LESS_EQUAL); }

"fe"          { return T_FE; }
"7alet"       { return T_7ALET; }

"thabet"      { return T_THABET; }
"sa7e7"       { RETURN_STR(T_SA7E7); }
"7a2i2i"      { RETURN_STR(T_7A2I2I); }
"tarqeem"     { return T_TARQEEM; }

"="           { return T_ASSIGNMENT; }
"+"           { RETURN_STR(T_PLUS); }
"-"           { RETURN_STR(T_NEG); }
"*"           { RETURN_STR(T_MULT); }
"/"           { RETURN_STR(T_DIV); }
"%"           { RETURN_STR(T_MODULO); }
"**"          { RETURN_STR(T_EXPONENT); }

"basy"        { return T_BASY; }

":"           { return T_COLON; }
";"           { return T_SEMICOLON; }
","           { return T_COMMA; }
"{"           { return T_CRULY_BR_BGN; }
"}"           { return T_CRULY_BR_END; }
"("           { return T_ROUND_BR_BGN; }
")"           { return T_ROUND_BR_END; }

{int_literal}       { RETURN_STR(T_INT_LITERAL); }
{real_literal}      { RETURN_STR(T_REAL_LITERAL); }
{tarqeem_instance}  { RETURN_STR(T_TARQEEM_INSTANCE); }
{symbol}            { RETURN_STR(T_SYMBOL); }

    /* invalid */
{rest_chars} {
    yyerror("unexpected character");
}

%%
