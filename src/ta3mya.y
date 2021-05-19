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
%type	<int_val>	int_exp
%type	<dbl_val>	real_exp
%start input

%%

input:
  /* empty */
  | input line
  ;

line:
  NEWLINE
  | int_exp NEWLINE	  { cout << "Result: " << $1 << endl; }
  | real_exp NEWLINE	{ cout << "Result: " << std::to_string($1) << endl; }
  ;

real_exp:
  T_REAL_LITERAL
  | T_7A2I2I T_ROUND_BR_BGN real_exp T_ROUND_BR_END { $$ = $3;             }
  | T_7A2I2I T_ROUND_BR_BGN int_exp T_ROUND_BR_END  { $$ = double($3);     }

  | real_exp T_PLUS real_exp	                      { $$ = $1 + $3;        }
  | real_exp T_PLUS int_exp	                        { $$ = $1 + double($3);}
  | int_exp T_PLUS real_exp	                        { $$ = double($1) + $3;}

  | real_exp T_NEG real_exp                         { $$ = $1 - $3;        }
  | real_exp T_NEG int_exp                          { $$ = $1 - double($3);}
  | int_exp T_NEG real_exp                          { $$ = double($1) - $3;}

  | real_exp T_MULT real_exp	                      { $$ = $1 * $3;        }
  | real_exp T_MULT int_exp	                        { $$ = $1 * double($3);}
  | int_exp T_MULT real_exp	                        { $$ = double($1) * $3;}

  | real_exp T_DIV real_exp                         { $$ = $1 / $3;        }
  | real_exp T_DIV int_exp                          { $$ = $1 / double($3);}
  | int_exp T_DIV real_exp                          { $$ = double($1) / $3;}

  | T_NEG real_exp %prec T_NEG                      { $$ = -$2;            }

  | real_exp T_EXPONENT real_exp                    { $$ = pow($1, $3);    }
  | real_exp T_EXPONENT int_exp                     {$$=pow($1,double($3));}
  | int_exp T_EXPONENT real_exp                     {$$=pow(double($1),$3);}

  | T_ROUND_BR_BGN real_exp T_ROUND_BR_END          { $$ = $2;             }
  ;

int_exp:
  T_INT_LITERAL
  | T_SA7E7 T_ROUND_BR_BGN real_exp T_ROUND_BR_END { $$ = int($3);     }
  | T_SA7E7 T_ROUND_BR_BGN int_exp T_ROUND_BR_END  { $$ = $3;          }
  | int_exp T_PLUS int_exp	                       { $$ = $1 + $3;     }
  | int_exp T_NEG int_exp                          { $$ = $1 - $3;     }
  | int_exp T_MULT int_exp	                       { $$ = $1 * $3;     }
  | int_exp T_DIV int_exp                          { $$ = $1 / $3;     }
  | T_NEG int_exp %prec T_NEG                      { $$ = -$2;         }
  | int_exp T_EXPONENT int_exp                     { $$ = pow($1, $3); }
  | T_ROUND_BR_BGN int_exp T_ROUND_BR_END          { $$ = $2;          }
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
