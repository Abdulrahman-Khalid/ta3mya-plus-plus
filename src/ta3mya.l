%{
#include "heading.h"
#include "ta3mya.tab.h"

int yyerror(char *s);
%}

%option yylineno

digit		            [0-9]
int_const	            {digit}+
real_const              {digit}+\.{digit}+
rest_chars              .
single_cmnt             "//".*\n
mult_cmnt               "/*"[^*/]*"*/"
whitespace              [ \t\n]*

%%

{int_const} { 
    yylval.int_val = atoi(yytext); 
    return INTEGER_LITERAL; 
}

"+" { return PLUS; }
"*" { return MULT; }

    /* ignored */
{single_cmnt}
{mult_cmnt}
{whitespace}

    /* invalid */
{rest_chars} {
    std::cerr << "SCANNER ";
    yyerror("");
    exit(1);
}

%%
