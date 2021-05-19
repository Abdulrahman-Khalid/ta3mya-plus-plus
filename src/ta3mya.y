%{
#include "heading.h"

int yyerror(char *s);
int yylex(void);
%}

%union{
  int int_val;
  double dbl_val;
  string* str_val;
}

// terminals
%token NEWLINE

%token T_LW
%token T_8ERO

%token T_LEF
%token T_L7D
%token T_TALMA

%token T_MSH
%token T_WE
%token T_AW

%token T_DOESNT_EQUAL
%token T_EQUALS
%token T_GREATER
%token T_GREATER_EQUAL
%token T_LESS
%token T_LESS_EQUAL

%token T_FARRAQ
%token T_7ALAH
%token T_KARRAR
%token T_ASSASY

%token T_THABET
%token T_SA7E7
%token T_7A2I2I

%token T_ASSIGNMENT
%left	T_PLUS T_NEG
%left	T_MULT T_DIV T_MODULO
%right T_EXPONENT

%token T_BEDAYAH
%token T_BASY

%token T_COLON
%token T_CRULY_BR_BGN
%token T_CRULY_BR_END
%token T_ROUND_BR_BGN
%token T_ROUND_BR_END

%token <int_val>	T_INT_LITERAL
%token <dbl_val>  T_REAL_LITERAL
%token <str_val>  T_SYMBOL

// non terminals
%type	<int_val>	exp
%start input

%%

input:
  /* empty */
  | input line
  ;

line:
  NEWLINE
  | exp NEWLINE	{ cout << "Result: " << $1 << endl; }
  ;

exp:
  T_INT_LITERAL
  | exp T_PLUS exp	                  { $$ = $1 + $3;     }
  | exp T_NEG exp                     { $$ = $1 - $3;     }
  | exp T_MULT exp	                  { $$ = $1 * $3;     }
  | exp T_DIV exp                     { $$ = $1 / $3;     }
  | T_NEG exp %prec NEG               { $$ = -$2;         }
  | exp T_EXPONENT exp                { $$ = pow($1, $3); }
  | T_ROUND_BR_BGN exp T_ROUND_BR_END { $$ = $2;          }
  ;

%%

int yyerror(string s) {
  extern int yylineno;	// defined and maintained in lex.c
  extern char *yytext;	// defined and maintained in lex.c

  if (s.size() > 0) {
    s = "ERROR: " + s;
  } else {
    s = "ERROR";
  }
  
  cerr << s << " at symbol \"" << yytext
      << "\" on line " << yylineno << endl;

  return 1;
}

int yyerror(char *s) {
  return yyerror(string(s));
}
