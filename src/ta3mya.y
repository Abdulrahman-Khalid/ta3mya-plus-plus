%{
#include "heading.h"

int yyerror(char *s);
int yylex(void);
%}

%union{
  int int_val;
}

// terminals
%token <int_val>	INTEGER_LITERAL
%left	PLUS
%left	MULT

// non terminals
%type	<int_val>	exp
%start input

%%

input:
  /* emtpy */
  | exp	{ cout << "Result: " << $1 << endl; }
  ;

exp:
  INTEGER_LITERAL
  | exp PLUS exp	{ $$ = $1 + $3; }
  | exp MULT exp	{ $$ = $1 * $3; }
  ;

%%

int yyerror(string s) {
  extern int yylineno;	// defined and maintained in lex.c
  extern char *yytext;	// defined and maintained in lex.c
  
  cerr << "ERROR: " << s << " at symbol \"" << yytext;
  cerr << "\" on line " << yylineno << endl;
  exit(1);
}

int yyerror(char *s) {
  return yyerror(string(s));
}
