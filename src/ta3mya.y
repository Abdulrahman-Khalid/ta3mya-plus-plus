%{
#include "heading.h"

int yyerror(char *s);
int yylex(void);

#define BOOL_STR(b) ((b)? "sa7":"8alat")
%}

%union{
  int int_val;
  double dbl_val;
  bool bool_val;
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


%token T_FARRAQ
%token T_7ALAH
%token T_KARRAR
%token T_ASSASY

%token T_THABET
%token T_SA7E7
%token T_7A2I2I

%token T_ASSIGNMENT

%left T_DOESNT_EQUAL T_EQUALS T_GREATER T_GREATER_EQUAL T_LESS T_LESS_EQUAL
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
%type	<bool_val>	condition
%type	<dbl_val>	real_exp
%start input

%%

input:
  /* empty */
  | input line
  ;

line:
  NEWLINE
  | int_exp NEWLINE	  { cout << "= " << $1 << endl; }
  | real_exp NEWLINE	{ cout << "= " << std::to_string($1) << endl; }
  | condition NEWLINE { cout << "= " << BOOL_STR($1) << endl; }
  | lw_group NEWLINE
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
  | T_SA7E7 T_ROUND_BR_BGN condition T_ROUND_BR_END { $$ = int($3);     }
  | T_SA7E7 T_ROUND_BR_BGN real_exp T_ROUND_BR_END  { $$ = int($3);     }
  | T_SA7E7 T_ROUND_BR_BGN int_exp T_ROUND_BR_END   { $$ = $3;          }
  | int_exp T_PLUS int_exp	                        { $$ = $1 + $3;     }
  | int_exp T_NEG int_exp                           { $$ = $1 - $3;     }
  | int_exp T_MULT int_exp	                        { $$ = $1 * $3;     }
  | int_exp T_DIV int_exp                           { $$ = $1 / $3;     }
  | T_NEG int_exp %prec T_NEG                       { $$ = -$2;         }
  | int_exp T_EXPONENT int_exp                      { $$ = pow($1, $3); }
  | T_ROUND_BR_BGN int_exp T_ROUND_BR_END           { $$ = $2;          }
  ;

condition:
  condition T_WE condition               { $$ = $1&&$3; }
  | condition T_AW condition             { $$ = $1||$3; }
  | T_MSH condition                      { $$ = !$2;    }

  | int_exp T_EQUALS int_exp             { $$ = $1==$3; }
  | int_exp T_EQUALS real_exp            { $$ = $1==$3; }
  | real_exp T_EQUALS int_exp            { $$ = $1==$3; }

  | int_exp T_DOESNT_EQUAL int_exp       { $$ = $1!=$3; }
  | int_exp T_DOESNT_EQUAL real_exp      { $$ = $1!=$3; }
  | real_exp T_DOESNT_EQUAL int_exp      { $$ = $1!=$3; }

  | int_exp T_GREATER int_exp            { $$ = $1>$3;  }
  | int_exp T_GREATER real_exp           { $$ = $1>$3;  }
  | real_exp T_GREATER int_exp           { $$ = $1>$3;  }

  | int_exp T_LESS int_exp               { $$ = $1<$3;  }
  | int_exp T_LESS real_exp              { $$ = $1<$3;  }
  | real_exp T_LESS int_exp              { $$ = $1<$3;  }

  | int_exp T_GREATER_EQUAL int_exp      { $$ = $1>=$3; }
  | int_exp T_GREATER_EQUAL real_exp     { $$ = $1>=$3; }
  | real_exp T_GREATER_EQUAL int_exp     { $$ = $1>=$3; }

  | int_exp T_LESS_EQUAL int_exp         { $$ = $1<=$3; }
  | int_exp T_LESS_EQUAL real_exp        { $$ = $1<=$3; }
  | real_exp T_LESS_EQUAL int_exp        { $$ = $1<=$3; }
  ;

  /* ensure one or zoro 8ero stmt at end */
lw_group: 
  lw_stmt 
  | lw_stmt T_8ERO block { cout << "8ero_stmt" << endl; }
  ;

  /* zero or more 8erolw stmts only after lw stmt */
lw_stmt:
  T_LW condition block { cout << "lw_stmt: " << BOOL_STR($2) << endl; }
  | lw_stmt T_8ERO T_LW condition block { cout << "8erolw_stmt: " << BOOL_STR($4) << endl; }
  ;

block:
  T_CRULY_BR_BGN T_CRULY_BR_END
  | T_CRULY_BR_BGN input T_CRULY_BR_END
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
