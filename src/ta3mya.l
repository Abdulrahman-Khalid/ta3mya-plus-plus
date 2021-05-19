%{
#include "heading.h"
#include "ta3mya.tab.h"

int yyerror(char *s);
%}

    // increment yylineno automatically
%option yylineno

digit		            [0-9]
int_literal	            {digit}+
real_literal            {digit}+\.{digit}+
rest_chars              .
symbol                  [a-zA-Z0-9]+
single_cmnt             "//".*\n
mult_cmnt               "/*"[^*/]*"*/"
whitespace              [ \t]*

%%

    /* ignored */
{single_cmnt} { }
{mult_cmnt}   { }
{whitespace}  { }

\n            { return NEWLINE; }

"lw"          { return T_LW; }
"8ero"        { return T_8ERO; }

"lef"         { return T_LEF; }
"l7d"         { return T_L7D; }
"talma"       { return T_TALMA; }

"msh"         { return T_MSH; }
"we"          { return T_WE; }
"aw"          { return T_AW; }

"!="          { return T_DOESNT_EQUAL; }
"=="          { return T_EQUALS; }
">"           { return T_GREATER; }
">="          { return T_GREATER_EQUAL; }
"<"           { return T_LESS; }
"<="          { return T_LESS_EQUAL; }

"farraq"      { return T_FARRAQ; }
"7alah"       { return T_7ALAH; }
"karrar"      { return T_KARRAR; }
"assasy"      { return T_ASSASY; }

"thabet"      { return T_THABET; }
"sa7e7"       { return T_SA7E7; }
"7a2i2i"      { return T_7A2I2I; }

"="           { return T_ASSIGNMENT; }
"+"           { return T_PLUS; }
"-"           { return T_NEG; }
"*"           { return T_MULT; }
"/"           { return T_DIV; }
"%"           { return T_MODULO; }
"**"          { return T_EXPONENT; }

"bedayah"     { return T_BEDAYAH; }
"basy"        { return T_BASY; }

":"           { return T_COLON; }
"{"           { return T_CRULY_BR_BGN; }
"}"           { return T_CRULY_BR_END; }
"("           { return T_ROUND_BR_BGN; }
")"           { return T_ROUND_BR_END; }

{int_literal} { 
    yylval.int_val = atoi(yytext); 
    return T_INT_LITERAL; 
}

{real_literal} { 
    yylval.dbl_val = strtod(yytext, NULL); 
    return T_REAL_LITERAL;
}

{symbol} {
    yylval.str_val = new std::string(yytext, yyleng);
    return T_SYMBOL;
}

    /* invalid */
{rest_chars} {
    std::cerr << "SCANNER ";
    yyerror("");
    exit(1);
}

%%
