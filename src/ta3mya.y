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
%token <str_val> T_WE
%token <str_val> T_AW

%token T_FE
%token T_7ALET
%token T_KARRAR

%token T_THABET
%token <str_val> T_SA7E7
%token <str_val> T_7A2I2I
%token T_TARQEEM

%token T_ASSIGNMENT

%left <str_val> T_DOESNT_EQUAL T_EQUALS T_GREATER T_GREATER_EQUAL T_LESS T_LESS_EQUAL
%left <str_val> T_PLUS T_NEG
%left <str_val> T_MULT T_DIV T_MODULO
%right <str_val> T_EXPONENT

%token T_BASY

%token T_COLON
%token T_SEMICOLON
%token T_COMMA
%token T_CRULY_BR_BGN
%token T_CRULY_BR_END
%token T_ROUND_BR_BGN
%token T_ROUND_BR_END

%token <str_val> T_SYMBOL
%token <str_val> T_TARQEEM_INSTANCE

%token <str_val> T_INT_LITERAL
%token <str_val> T_REAL_LITERAL

// non terminals
%start                    program
%type <prgnodeptr_val>    program
%type <expr_val> exp
%type <stmt_val> stmt

%type <block_stmt_val> block
%type <basy_stmt_val> basy_stmt

%type <lw_stmt_val> lw_stmt
%type <lw_stmt_val> halet_stmt
%type <lw_group_val> lw_group
%type <lw_group_val> fe7alet_stmt

%type <karrar_l7d_val> karrar_l7d_stmt
%type <talma_val> talma_stmt

%type <expr_val> binary_exp
%type <expr_val> unary_exp
%type <expr_val> call_dallah

%type <str_val>  type
%type <str_val>  binary_operator
%type <str_val>  comparator

%type <tarqeemlist_val> tarqeem_list
%type <stmt_val>        ta3reef_tarqeem

%type <args_val>  args

%union{
  string* str_val;
  Expression* expr_val;
  ProgramNode* prgnodeptr_val;
  BasyStatement* basy_stmt_val;
  BlockStatement* block_stmt_val;
  Statement* stmt_val;
  LwStatement* lw_stmt_val;
  LwGroupStatement* lw_group_val;
  TarqeemList* tarqeemlist_val;
  CallDallahArgs* args_val;
  KarrarL7dStatement* karrar_l7d_val;
  TalmaStatement* talma_val;
}

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
  | lw_group          { $$ = $1; }
  | talma_stmt        { $$ = $1; }
  | karrar_l7d_stmt   { $$ = $1; }
  | ta3reef_mota8ier
  | ta3reef_thabet
  | ta3reef_dallah
  | ta3reef_tarqeem   { $$ = $1; }
  | assignment
  | fe7alet_stmt      { $$ = $1; }
  | lef_stmt
  | block             { $$ = $1; }
  ;

exp: 
  T_SYMBOL         { $$ = new SymbolExpression(*($1)); }
  | T_INT_LITERAL  { $$ = new Literal(*($1)); }
  | T_REAL_LITERAL { $$ = new Literal(*($1)); }
  | binary_exp
  | unary_exp
  | call_dallah
  ;

binary_operator: T_PLUS | T_NEG | T_MULT | T_DIV | T_MODULO | T_EXPONENT | T_WE | T_AW;
comparator: T_DOESNT_EQUAL | T_EQUALS | T_GREATER | T_GREATER_EQUAL | T_LESS | T_LESS_EQUAL;

binary_exp: 
  exp binary_operator exp { $$ = new BinaryExpression($1, *($2), $3); }
  | exp comparator exp    { $$ = new BinaryExpression($1, *($2), $3); }
  ;

unary_exp: 
  T_NEG exp %prec T_NEG  { $$ = new NegExpression($2); } 
  | T_MSH exp            { $$ = new MshExpression($2);             } 
  | T_PLUS exp %prec T_PLUS { $$ = $2; }
  ;

args:
  /* empty  */         { $$ = new CallDallahArgs();     }
  | exp                { $$ = new CallDallahArgs({$1}); }
  | args T_COMMA exp   { $1->push_back($3); $$ = $1;    }
  ;

call_dallah:
  T_SYMBOL T_ROUND_BR_BGN args T_ROUND_BR_END { $$ = new CallDallahExpression(*$1, *$3); }
  ;

  /* ensure one or zero 8ero stmt at end */
lw_group:
  lw_stmt                 { $$ = new LwGroupStatement($1); /*cout << $$->toString() << endl;*/ }
  | lw_stmt T_8ERO block  { $$ = new LwGroupStatement($1, $3); /*cout << $$->toString() << endl;*/ }
  ;

  /* zero or more 8erolw stmts only after lw stmt */
lw_stmt:
  T_LW exp block { $$ = new LwStatement(); $$->addConditionalBlock($2, $3); }
  | lw_stmt T_8ERO T_LW exp block { $1->addConditionalBlock($4, $5); }
  ;

fe7alet_stmt:
  T_SYMBOL T_FE halet_stmt                { $$ = new LwGroupStatement($3); }
  | T_SYMBOL T_FE halet_stmt T_8ERO block { $$ = new LwGroupStatement($3, $5); }
  ;

halet_stmt:
  T_7ALET exp block               { $$ = new LwStatement(); $$->addConditionalBlock($2, $3); }
  | halet_stmt T_7ALET exp block  { $1->addConditionalBlock($3, $4); }
  ;

talma_stmt:
  T_TALMA exp block { $$ = new TalmaStatement($2, $3); }
  ;

karrar_l7d_stmt:
  T_KARRAR block T_L7D exp { $$ = new KarrarL7dStatement($4, $2); }
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

lef_init: assignment | ta3reef_mota8ier;
lef_stmt:
  T_LEF lef_init T_SEMICOLON exp T_SEMICOLON assignment block
    { cout << "lef_stmt" << endl; }
  ;

ta3reef_tarqeem:
  T_TARQEEM T_SYMBOL T_CRULY_BR_BGN tarqeem_list T_CRULY_BR_END { $$ = new Ta3reefTarqeemStatement(*$2, *$4); }
  ;

emtpyness:
  /* empty */
  | emtpyness T_NEWLINE
  ;

tarqeem_list:
  emtpyness T_SYMBOL emtpyness        { $$ = new TarqeemList({*$2}); }
  | tarqeem_list T_COMMA tarqeem_list {
    $1->insert($1->end(), $3->begin(), $3->end()); 
    delete $3;
  }
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
