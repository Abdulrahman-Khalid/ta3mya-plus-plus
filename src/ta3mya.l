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
symbol                  [a-zA-Z0-9]
single_cmnt             "//".*\n
mult_cmnt               "/*"[^*/]*"*/"
whitespace              [ \t\n]*

%%
    /* ignored */
{single_cmnt}
{mult_cmnt}
{whitespace}

"lw" // TODO
"8ero" // TODO

"lef" // TODO
"l7d" // TODO
"talma" // TODO

"msh" // TODO
"we" // TODO
"aw" // TODO
"!=" // TODO
"==" // TODO
">" // TODO
">=" // TODO
"<" // TODO
"<=" // TODO

"farraq" // TODO
"7alah" // TODO
"karrar" // TODO
"assasy" // TODO

"thabet" // TODO
"sa7e7" // TODO
"7a2i2i" // TODO

"=" // TODO
"+" { return PLUS; }
"-" // TODO
"*" { return MULT; }
"%" // TODO

"bedayah" // TODO
"basy" // TODO

":" // TODO
"{" // TODO
"}" // TODO
"(" // TODO
")" // TODO

{symbol} // TODO

{int_const} { 
    yylval.int_val = atoi(yytext); 
    return INTEGER_LITERAL; 
}

{real_const} { 
    yylval.int_val = strtod(yytext, NULL); 
    // TODO 
}

    /* invalid */
{rest_chars} {
    std::cerr << "SCANNER ";
    yyerror("");
    exit(1);
}

%%
