%{
#include "heading.h"
#include "ta3mya.tab.h"

int yyerror(char *s);
extern "C" int yylex(void);

#define RETURN_STR(t) do { yylval.str_val = new std::string(yytext, yyleng); return (t); } while(0)
#define RETURN_OPR(t) do { yylval.oper_val = t; return (T_##t); } while(0)
%}

    // increment yylineno automatically
%option yylineno

digit            [0-9]
int_literal      {digit}+
dbl_literal      {digit}+\.{digit}+
rest_chars       .
symbol           [a-zA-Z0-9_]+
tarqm_inst       {symbol}::{symbol}
single_cmnt      "//".*
mult_cmnt        "/*"[^*/]*"*/"
whitespace       [ \t]*

%%

    /* ignored */
{single_cmnt}    { }
{mult_cmnt}      { }
{whitespace}     { }

\n               { return T_NEWLINE; }

"lw"             { return T_LW; }
"8ero"           { return T_8ERO; }

"lef"            { return T_LEF; }
"l7d"            { return T_L7D; }
"talma"          { return T_TALMA; }
"karrar"         { return T_KARRAR; }

"msh"            { return T_MSH; }
"we"             { RETURN_OPR(WE); }
"aw"             { RETURN_OPR(AW); }

"!="             { RETURN_OPR(DOESNT_EQUAL); }
"=="             { RETURN_OPR(EQUALS); }
">"              { RETURN_OPR(GREATER); }
">="             { RETURN_OPR(GREATER_EQUAL); }
"<"              { RETURN_OPR(LESS); }
"<="             { RETURN_OPR(LESS_EQUAL); }

"fe"             { return T_FE; }
"7alet"          { return T_7ALET; }

"thabet"         { return T_THABET; }
"sa7e7"          { RETURN_STR(T_SA7E7); }
"7a2i2i"         { RETURN_STR(T_7A2I2I); }
"tarqeem"        { return T_TARQEEM; }

"="              { return T_ASSIGNMENT; }
"+"              { RETURN_OPR(PLUS); }
"-"              { RETURN_OPR(NEG); }
"*"              { RETURN_OPR(MULT); }
"/"              { RETURN_OPR(DIV); }
"%"              { RETURN_OPR(MODULO); }
"**"             { RETURN_OPR(EXPONENT); }

"basy"           { return T_BASY; }

":"              { return T_COLON; }
";"              { return T_SEMICOLON; }
","              { return T_COMMA; }
"{"              { return T_CRULY_BR_BGN; }
"}"              { return T_CRULY_BR_END; }
"("              { return T_ROUND_BR_BGN; }
")"              { return T_ROUND_BR_END; }

{int_literal}    { RETURN_STR(T_INT_LITERAL); }
{dbl_literal}    { RETURN_STR(T_REAL_LITERAL); }
{tarqm_inst}     { RETURN_STR(T_TARQEEM_INSTANCE); }
{symbol}         { RETURN_STR(T_SYMBOL); }

    /* invalid */
{rest_chars}     { yyerror("unexpected character"); }

%%
