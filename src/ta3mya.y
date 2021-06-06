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

%token T_FE
%token T_7ALET
%token T_KARRAR

%token T_THABET
%token <str_val> T_SA7E7
%token <str_val> T_7A2I2I
%token T_TARQEEM

%token T_ASSIGNMENT

%left <str_val> T_DOESNT_EQUAL T_EQUALS T_GREATER T_GREATER_EQUAL T_LESS T_LESS_EQUAL
%left <str_val> T_MSH
%left <str_val> T_WE T_AW

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
%type <halet_stmt_val> halet_stmt
%type <lw_group_val> lw_group
%type <lw_group_val> fe7alet_stmt

%type <karrar_l7d_val> karrar_l7d_stmt
%type <talma_val> talma_stmt
%type <lef_val> lef_stmt

%type <assignment_val> assignment
%type <ta3reef_mota8ier_val> ta3reef_mota8ier arg_decl
%type <ta3reef_thabet_val> ta3reef_thabet
%type <ta3reef_dallah_val> ta3reef_dallah
%type <ta3reef_dallah_args_val> args_decl

%type <expr_val> binary_exp
%type <expr_val> unary_exp
%type <expr_val> cast_exp
%type <expr_val> bool_exp
%type <expr_val> call_dallah

%type <type_val>  type
%type <str_val>  binary_operator
%type <str_val>  bool_comparator bool_compinator

%type <tarqeemlist_val> tarqeem_list
%type <stmt_val>        ta3reef_tarqeem

%type <call_args_val>  args

%union{
  string* str_val;
  Expression* expr_val;
  ProgramNode* prgnodeptr_val;
  BasyStatement* basy_stmt_val;
  BlockStatement* block_stmt_val;
  Statement* stmt_val;
  LwStatement* lw_stmt_val;
  HaletStatement* halet_stmt_val;
  LwGroupStatement* lw_group_val;
  TarqeemList* tarqeemlist_val;
  CallDallahArgs* call_args_val;
  KarrarL7dStatement* karrar_l7d_val;
  TalmaStatement* talma_val;
  LefStatement* lef_val;
  AssignmentStatement* assignment_val;
  Ta3reefMota8ierStatement* ta3reef_mota8ier_val;
  Ta3reefThabetStatement* ta3reef_thabet_val;
  Ta3reefDallahStatement* ta3reef_dallah_val;
  ArgsDeclarationStatement* ta3reef_dallah_args_val;
  Type type_val;
}

%%

program:
  /* empty */ {
    auto programnode = new ProgramNode();
    if (prgnodeptr == nullptr) { prgnodeptr = programnode; }
    $$ = programnode;    
  }
  | program stmt              { $1->addStatement($2); }
  | program stmt T_NEWLINE    { $1->addStatement($2); }
  | program T_NEWLINE         { $$ = $1; /*DEBUG($$->toString());*/ }
  ;

  /* {<program>} */
block: 
  T_CRULY_BR_BGN program T_CRULY_BR_END {
    $$ = new BlockStatement($2);
    /*DEBUG($$->toString());*/
  }
  ;

stmt:
  basy_stmt
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
  | block
  ;

exp: 
  T_SYMBOL                                 { $$ = new SymbolExpression(*$1);          }
  | T_TARQEEM_INSTANCE                     { $$ = new TarqeemInstanceExpression(*$1); }
  | T_INT_LITERAL                          { $$ = new Literal(*$1);                   }
  | T_REAL_LITERAL                         { $$ = new Literal(*$1);                   }
  | binary_exp
  | unary_exp
  | cast_exp
  | bool_exp
  | call_dallah
  | T_ROUND_BR_BGN exp T_ROUND_BR_END
  ;

binary_operator: T_PLUS | T_NEG | T_MULT | T_DIV | T_MODULO | T_EXPONENT;
binary_exp: 
  exp binary_operator exp { $$ = new BinaryExpression($1, *$2, $3); }
  ;

bool_compinator: T_WE | T_AW;
bool_comparator: T_DOESNT_EQUAL | T_EQUALS | T_GREATER | T_GREATER_EQUAL | T_LESS | T_LESS_EQUAL;
bool_exp:
  bool_exp bool_compinator bool_exp         { $$ = new BinaryExpression($1, *$2, $3); }
  | exp bool_comparator exp                 { $$ = new BinaryExpression($1, *$2, $3); }
  | T_ROUND_BR_BGN bool_exp T_ROUND_BR_END  { $$ = $2;                                }
  ;

unary_exp: 
  T_NEG exp %prec T_NEG     { $$ = new NegExpression($2); }
  | T_MSH exp               { $$ = new MshExpression($2); }
  | T_PLUS exp %prec T_PLUS { $$ = $2; }
  ;

cast_exp:
  T_SA7E7 T_ROUND_BR_BGN exp T_ROUND_BR_END     { $$ = new ToSa7e7Expression($3);  /*DEBUG($$->toString());*/}
  | T_7A2I2I T_ROUND_BR_BGN exp T_ROUND_BR_END  { $$ = new To7a2i2iExpression($3); /*DEBUG($$->toString());*/}
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
  lw_stmt                 { $$ = new LwGroupStatement($1);     /*DEBUG($$->toString());*/ }
  | lw_stmt T_8ERO block  { $$ = new LwGroupStatement($1, $3); /*DEBUG($$->toString());*/ }
  ;

  /* zero or more 8erolw stmts only after lw stmt */
lw_stmt:
  T_LW exp block                    { $$ = new LwStatement(); $$->addConditionalBlock($2, $3); }
  | lw_stmt T_8ERO T_LW exp block   { $1->addConditionalBlock($4, $5); }
  ;

fe7alet_stmt:
  T_SYMBOL T_FE halet_stmt {
    auto symbol = new SymbolExpression(*$1);
    $3->attachSymbol(symbol);
    $$ = new LwGroupStatement($3);
  }
  | T_SYMBOL T_FE halet_stmt T_8ERO block {
    auto symbol = new SymbolExpression(*$1);
    $3->attachSymbol(symbol);
    $$ = new LwGroupStatement($3, $5);
  }
  ;

halet_stmt:
  T_7ALET exp block               { $$ = new HaletStatement(); $$->addConditionalBlock($2, $3); }
  | halet_stmt T_7ALET exp block  { $1->addConditionalBlock($3, $4); }
  ;

talma_stmt:
  T_TALMA exp block { $$ = new TalmaStatement($2, $3); }
  ;

karrar_l7d_stmt:
  T_KARRAR block T_L7D exp { $$ = new KarrarL7dStatement($4, $2); }
  ;

basy_stmt:
  T_BASY exp { $$ = new BasyStatement($2); /*DEBUG($$->toString());*/ }
  ;

type:
  T_7A2I2I    { $$ = Type::REAL; }
  | T_SA7E7   { $$ = Type::INT;  }
  | T_SYMBOL  { $$ = Type::ENUM; }
  ;

ta3reef_mota8ier:
  type T_SYMBOL                     { $$ = new Ta3reefMota8ierStatement($1, *$2); }
  | type T_SYMBOL T_ASSIGNMENT exp  { $$ = new Ta3reefMota8ierStatement($1, *$2, $4); }
  ;

ta3reef_thabet:
  T_THABET type T_SYMBOL                     { yyerror("maynfa3sh te3mel const men 8er initial value"); }
  | T_THABET type T_SYMBOL T_ASSIGNMENT exp  { $$ = new Ta3reefThabetStatement($2, *$3, $5); }
  ;

arg_decl:
  type T_SYMBOL { $$ = new Ta3reefMota8ierStatement($1, *$2); }
  ;

args_decl:
  /* empty */                   { $$ = new ArgsDeclarationStatement(); }
  | arg_decl                    { $$ = new ArgsDeclarationStatement(); $$->addArgDeclaration($1); }
  | args_decl T_COMMA arg_decl  { $1->addArgDeclaration($3); }
  ;

ta3reef_dallah:
  type T_SYMBOL T_ROUND_BR_BGN args_decl T_ROUND_BR_END block {
    $$ = new Ta3reefDallahStatement($1, *$2, $4, $6);
  }
  ;

assignment:
  T_SYMBOL T_ASSIGNMENT exp { $$ = new AssignmentStatement(*$1, $3); }
  ;

lef_stmt:
  T_LEF assignment T_SEMICOLON exp T_SEMICOLON assignment block
    { $$ = new LefStatement($2, $4, $6, $7); }
  | T_LEF ta3reef_mota8ier T_SEMICOLON exp T_SEMICOLON assignment block
    { $$ = new LefStatement($2, $4, $6, $7); }
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
