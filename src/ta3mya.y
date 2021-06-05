%{
#include "heading.h"

int yyerror(char *s);
extern "C" int yylex(void);

#define BOOL_STR(b) ((b)? "sa7":"8alat")

ProgramNode * prgnodeptr = nullptr;
%}

// terminals
%token T_NEWLINE

%token T_LW
%token T_8ERO

%token T_LEF
%token T_L7D
%token T_TALMA

%token T_MSH
%token T_WE
%token T_AW

%token T_FE
%token T_7ALET
%token T_KARRAR

%token T_THABET
%token T_SA7E7
%token T_7A2I2I
%token T_TARQEEM

%token T_ASSIGNMENT

%left T_DOESNT_EQUAL T_EQUALS T_GREATER T_GREATER_EQUAL T_LESS T_LESS_EQUAL
%left T_PLUS T_NEG
%left T_MULT T_DIV T_MODULO
%right T_EXPONENT

%token T_BASY

%token T_COLON
%token T_SEMICOLON
%token T_COMMA
%token T_CRULY_BR_BGN
%token T_CRULY_BR_END
%token T_ROUND_BR_BGN
%token T_ROUND_BR_END

%token <str_val>  T_INT_LITERAL T_REAL_LITERAL T_SYMBOL T_TARQEEM_INSTANCE

// non terminals
%type <expr_val>  int_str real_str int_exp real_exp bool_exp exp

%type <prgnodeptr_val>    program

%type <stmt_val> stmt

%type <block_stmt_val> block

%type <basy_stmt_val> basy_stmt

%union{
  string* str_val;
  Expression* expr_val;
  ProgramNode* prgnodeptr_val;
  BasyStatement* basy_stmt_val;
  BlockStatement* block_stmt_val;
  Statement* stmt_val;
}

%start                    program

%%

program:
  /* empty */ {
    ProgramNode * programnode = new ProgramNode();
    if (prgnodeptr == nullptr) { prgnodeptr = programnode; }
    $$ = programnode;    
  }
  | program stmt              { $1->addStatement($2); }
  | program stmt T_NEWLINE    { $1->addStatement($2); }
  | program T_NEWLINE         { $$ = $1; /*cout << $$->toString() << endl;*/ }
  ;

  /* {<program>} */
block: 
  T_CRULY_BR_BGN program T_CRULY_BR_END {
    $$ = new BlockStatement($2);
    /*cout << $$->toString() << endl;*/
  }
  ;

stmt:
  basy_stmt           { $$ = $1; }
  | lw_group
  | talma_stmt
  | karrar_l7d_stmt
  | ta3reef_mota8ier
  | ta3reef_thabet
  | ta3reef_dallah
  | ta3reef_tarqeem
  | assignment
  | fe7alet_stmt
  | lef_stmt
  | block             { $$ = $1; }
  ;

exp:
  int_exp         { $$ = $1; /*cout << $$->toString() << endl;*/ }
  | real_exp      { $$ = $1; /*cout << $$->toString() << endl;*/ }
  | bool_exp      { $$ = $1; /*cout << $$->toString() << endl;*/ }
  | call_dallah
  ;

real_str:
  T_REAL_LITERAL                                    { $$ = new Literal(*$1);   } 
  | T_SYMBOL                                        { $$ = new SymbolExpression(*$1);     } 
  ;

real_exp:
  real_str   
  | T_7A2I2I T_ROUND_BR_BGN int_exp T_ROUND_BR_END  { $$ = new To7a2i2i($3);                      }
  | T_7A2I2I T_ROUND_BR_BGN real_exp T_ROUND_BR_END { $$ = new To7a2i2i($3);                     }

  | real_exp T_PLUS real_exp                        { $$ = new RealExpression($1, "+" ,$3);     }
  | real_exp T_PLUS int_exp                         { Expression * to7a2i2i = new To7a2i2i($3);
                                                      $$ = new RealExpression($1, "+" ,to7a2i2i); }
  | int_exp T_PLUS real_exp                         { Expression * to7a2i2i = new To7a2i2i($1);
                                                      $$ = new RealExpression(to7a2i2i, "+" ,$3); }

  | real_exp T_NEG real_exp                         { $$ = new RealExpression($1, "-" ,$3);     }
  | real_exp T_NEG int_exp                          { Expression * to7a2i2i = new To7a2i2i($3);
                                                      $$ = new RealExpression($1, "-" ,to7a2i2i); }
  | int_exp T_NEG real_exp                          { Expression * to7a2i2i = new To7a2i2i($1);
                                                      $$ = new RealExpression(to7a2i2i, "-" ,$3); }

  | real_exp T_MULT real_exp                        { $$ = new RealExpression($1, "*" ,$3);     }
  | real_exp T_MULT int_exp                         { Expression * to7a2i2i = new To7a2i2i($3);
                                                      $$ = new RealExpression($1, "*" ,to7a2i2i); }
  | int_exp T_MULT real_exp                         { Expression * to7a2i2i = new To7a2i2i($1);
                                                      $$ = new RealExpression(to7a2i2i, "*" ,$3); }

  | real_exp T_DIV real_exp                         { $$ = new RealExpression($1, "/" ,$3);     }
  | real_exp T_DIV int_exp                          { Expression * to7a2i2i = new To7a2i2i($3);
                                                      $$ = new RealExpression($1, "/" ,to7a2i2i); }
  | int_exp T_DIV real_exp                          { Expression * to7a2i2i = new To7a2i2i($1);
                                                      $$ = new RealExpression(to7a2i2i, "/" ,$3); }

  | real_exp T_MODULO int_exp                       { Expression * to7a2i2i = new To7a2i2i($3);
                                                      $$ = new RealExpression($1, "%" ,to7a2i2i); }
  | T_NEG real_exp %prec T_NEG                      { $$ = new Salb7a2i2i($2);                     }

  | real_exp T_EXPONENT real_exp                    { $$ = new RealExpression($1, "**" ,$3);     }
  | real_exp T_EXPONENT int_exp                     { Expression * to7a2i2i = new To7a2i2i($3);
                                                      $$ = new RealExpression($1, "**" ,to7a2i2i);}
  | int_exp T_EXPONENT real_exp                     { Expression * to7a2i2i = new To7a2i2i($1);
                                                      $$ = new RealExpression(to7a2i2i, "**" ,$3);}

  | T_ROUND_BR_BGN real_exp T_ROUND_BR_END          { $$ = $2;             }
  ;

int_str:
  T_INT_LITERAL                                     { $$ = new Literal(*$1);               }
  | T_SYMBOL                                        { $$ = new SymbolExpression(*$1);                } 
  ;

int_exp:
  int_str
  | T_TARQEEM_INSTANCE                              { $$ = 0;                              }
  | T_SA7E7 T_ROUND_BR_BGN bool_exp T_ROUND_BR_END  { $$ = new ToSa7e7($3);                }
  | T_SA7E7 T_ROUND_BR_BGN real_exp T_ROUND_BR_END  { $$ = new ToSa7e7($3);                }
  | T_SA7E7 T_ROUND_BR_BGN int_exp T_ROUND_BR_END   { $$ = new ToSa7e7($3);                }
  | int_exp T_PLUS int_exp                          { $$ = new IntExpression($1, "+" ,$3); }
  | int_exp T_NEG int_exp                           { $$ = new IntExpression($1, "-" ,$3); }
  | int_exp T_MULT int_exp                          { $$ = new IntExpression($1, "*" ,$3); }
  | int_exp T_DIV int_exp                           { $$ = new IntExpression($1, "/" ,$3); }
  | int_exp T_MODULO int_exp                        { $$ = new IntExpression($1, "%" ,$3); }
  | T_NEG int_exp %prec T_NEG                       { $$ = new SalbS7e7($2);                 }
  | int_exp T_EXPONENT int_exp                      { $$ = new IntExpression($1, "**" ,$3);}
  | T_ROUND_BR_BGN int_exp T_ROUND_BR_END           { $$ = $2;          }
  ;

bool_exp:
  bool_exp T_WE bool_exp                 { $$ = new BoolExpression($1, "&&" ,$3); }
  | bool_exp T_AW bool_exp               { $$ = new BoolExpression($1, "||" ,$3); }
  | T_MSH bool_exp                       { $$ = new Msh($2);                      }

  | int_exp T_EQUALS int_exp             { $$ = new BoolExpression($1, "==" ,$3); }
  | int_exp T_EQUALS real_exp            { $$ = new BoolExpression($1, "==" ,$3); }
  | real_exp T_EQUALS int_exp            { $$ = new BoolExpression($1, "==" ,$3); }
  | real_exp T_EQUALS real_exp           { $$ = new BoolExpression($1, "==" ,$3); }

  | int_exp T_DOESNT_EQUAL int_exp       { $$ = new BoolExpression($1, "!=" ,$3); }
  | int_exp T_DOESNT_EQUAL real_exp      { $$ = new BoolExpression($1, "!=" ,$3); }
  | real_exp T_DOESNT_EQUAL int_exp      { $$ = new BoolExpression($1, "!=" ,$3); }
  | real_exp T_DOESNT_EQUAL real_exp     { $$ = new BoolExpression($1, "!=" ,$3); }

  | int_exp T_GREATER int_exp            { $$ = new BoolExpression($1, ">" ,$3); }
  | int_exp T_GREATER real_exp           { $$ = new BoolExpression($1, ">" ,$3); }
  | real_exp T_GREATER int_exp           { $$ = new BoolExpression($1, ">" ,$3); }
  | real_exp T_GREATER real_exp          { $$ = new BoolExpression($1, ">" ,$3); }

  | int_exp T_LESS int_exp               { $$ = new BoolExpression($1, "<" ,$3); }
  | int_exp T_LESS real_exp              { $$ = new BoolExpression($1, "<" ,$3); }
  | real_exp T_LESS int_exp              { $$ = new BoolExpression($1, "<" ,$3); }
  | real_exp T_LESS real_exp             { $$ = new BoolExpression($1, "<" ,$3); }

  | int_exp T_GREATER_EQUAL int_exp      { $$ = new BoolExpression($1, ">=" ,$3); }
  | int_exp T_GREATER_EQUAL real_exp     { $$ = new BoolExpression($1, ">=" ,$3); }
  | real_exp T_GREATER_EQUAL int_exp     { $$ = new BoolExpression($1, ">=" ,$3); }
  | real_exp T_GREATER_EQUAL real_exp    { $$ = new BoolExpression($1, ">=" ,$3); }

  | int_exp T_LESS_EQUAL int_exp         { $$ = new BoolExpression($1, "<=" ,$3); }
  | int_exp T_LESS_EQUAL real_exp        { $$ = new BoolExpression($1, "<=" ,$3); }
  | real_exp T_LESS_EQUAL int_exp        { $$ = new BoolExpression($1, "<=" ,$3); }
  | real_exp T_LESS_EQUAL real_exp       { $$ = new BoolExpression($1, "<=" ,$3); }
  ;

  /* ensure one or zoro 8ero stmt at end */
lw_group:
  lw_stmt
  | lw_stmt T_8ERO block { cout << "8ero_stmt" << endl; }
  ;

  /* zero or more 8erolw stmts only after lw stmt */
lw_stmt:
  T_LW bool_exp block                  { cout << "lw_stmt: " << BOOL_STR($2) << endl;     }
  | lw_stmt T_8ERO T_LW bool_exp block { cout << "8erolw_stmt: " << BOOL_STR($4) << endl; }
  ;

talma_stmt:
  T_TALMA bool_exp block { cout << "talma_stmt: " << BOOL_STR($2) << endl; }
  ;

karrar_l7d_stmt:
  T_KARRAR block T_L7D bool_exp { cout << "karrar_l7d_stmt: " << BOOL_STR($4) << endl; }
  ;

basy_stmt:
  T_BASY exp { $$ = new BasyStatement($2); /*cout << $$->toString() << endl;*/ }
  ;

type: T_7A2I2I | T_SA7E7 | T_SYMBOL;

ta3reef_mota8ier:
  type T_SYMBOL                     { cout << "ta3reef_mota8ier: " << *($2) << endl; }
  | type T_SYMBOL T_ASSIGNMENT exp  { cout << "ta3reef_mota8ier: " << *($2) << endl; }
  ;

ta3reef_thabet:
  T_THABET type T_SYMBOL                     { yyerror("maynfa3sh te3mel const men 8er initial value"); }
  | T_THABET type T_SYMBOL T_ASSIGNMENT exp  { cout << "ta3reef_thabet: " << *($3) << endl; }
  ;

arg_decl: type T_SYMBOL;
args_decl: /* empty */ | arg_decl | args_decl T_COMMA arg_decl;

ta3reef_dallah:
  type T_SYMBOL T_ROUND_BR_BGN args_decl T_ROUND_BR_END block { cout << "ta3reef_dallah: " << *($2) << endl; }
  ;

assignment:
  T_SYMBOL T_ASSIGNMENT exp { cout << "assignemnt to " << *($1) << endl; }
  ;

fe7alet_stmt:
  T_SYMBOL T_FE halet_stmt                { cout << "fe7alet_stmt: " << *($1) << endl;      }
  | T_SYMBOL T_FE halet_stmt T_8ERO block { cout << "fe7alet_stmt+8ero: " << *($1) << endl; }
  ;

halet_stmt:
  T_7ALET exp block
  | halet_stmt T_7ALET exp block
  ;

lef_init: assignment | ta3reef_mota8ier;
lef_stmt:
  T_LEF lef_init T_SEMICOLON bool_exp T_SEMICOLON assignment block
    { cout << "lef_stmt" << endl; }
  ;

args:
  /* empty  */
  | exp
  | args T_COMMA exp
  ;

call_dallah:
  T_SYMBOL T_ROUND_BR_BGN args T_ROUND_BR_END { cout << "call_dallah: " << *($1) << endl; }
  ;

ta3reef_tarqeem:
  T_TARQEEM T_SYMBOL T_CRULY_BR_BGN tarqeem_list T_CRULY_BR_END { cout << "ta3reef_tarqeem: " << *($2) << endl; }
  ;

emtpyness:
  /* empty */
  | emtpyness T_NEWLINE
  ;

tarqeem_list:
  emtpyness T_SYMBOL emtpyness
  | tarqeem_list T_COMMA tarqeem_list
  ;

%%

int yyerror(string s) {
  extern int yylineno;    // defined and maintained in lex.c
  extern char *yytext;    // defined and maintained in lex.c

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
