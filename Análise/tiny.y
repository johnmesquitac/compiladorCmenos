/****************************************************/
/* File: tiny.y                                     */
/* The TINY Yacc/Bison specification file           */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/
%{
#define YYPARSER /* distinguishes Yacc output from other code files */

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

#define YYSTYPE TreeNode *
static char * savedName; /* for use in assignments */
static int savedLineNo;  /* ditto */
static TreeNode * savedTree; /* stores syntax tree for later return */
static int yylex(void);


%}

%token IF THEN ELSE INT RETURN VOID WHILE
%token ID NUM 
%token ASSIGN EQ LT PLUS MINUS TIMES OVER LPAREN RPAREN SEMI NEQ LTEQ GT GTEQ COMMA LBRACKET RBRACKET LBRACE RBRACE
%token ERROR 

%% /* Grammar for CMENOS*/

programa 				: decl-lista {savedTree = $1;}
						;

decl-lista 				: decl-lista decl {
							YYSTYPE t = $1;
							if (t != NULL) {
								while (t->sibling != NULL) {
									t = t->sibling;
								}
								t->sibling = $2;
								$$ = $1;
							} else {
								$$ = $2;
							}
						}
						| decl {$$ = $1;}
						;

decl 					: var-decl {$$ = $1;} 
						| fun-decl {$$ = $1;}
						;

var-decl 				: tipo-especificador id SEMI {
							$$ = $1;
							$$->child[0] = $2;
							$$->child[0]->kind.exp = VariableK;
							$$->child[0]->type = $$->type;
						}
						| tipo-especificador id LBRACKET num RBRACKET SEMI {
							$$ = $1;
							$$->child[0] = $2;
							$$->child[0]->kind.exp = VectorK;
							$$->child[0]->child[0] = $4;
							$$->child[0]->type = $$->type;
						}
						;

tipo-especificador 		: INT {
							$$ = newExpNode(TypeK);
							$$->type = Int;
						}
						| VOID {
							$$ = newExpNode(TypeK);
							$$->type = Void;
						}
						;

fun-decl 				: tipo-especificador id LPAREN params RPAREN composto-decl {
							$$ = $1;
							$$->child[0] = $2;
							$$->child[0]->kind.exp = FunctionK;
							$$->child[0]->type = $$->type;
							$$->child[0]->child[0] = $4;
							$$->child[0]->child[1] = $6;
						}
						;

params 					: param-lista {$$ = $1;} 
						| VOID {
							$$ = newExpNode(TypeK);
							$$->type = Void;
						}
						;

param-lista 			: param-lista COMMA param {
							YYSTYPE t = $1;
							if (t != NULL) {
								while (t->sibling != NULL) {
									t = t->sibling;
								}
								t->sibling = $3;
								$$ = $1;
							} else {
								$$ = $3;
							}
						}
						| param {$$ = $1;}
						;

param 					: tipo-especificador id {
							$$ = $1;
							$$->child[0] = $2;
							$$->child[0]->kind.exp = VariableK;
							$$->child[0]->type = $$->type;
						}
						| tipo-especificador id LBRACKET RBRACKET {
							$$ = $1;
							$$->child[0] = $2;
							$$->child[0]->kind.exp = VectorK;
							$$->child[0]->type = $$->type;
						}
						;

composto-decl 			: LBRACE local-decl statement-lista RBRACE {
							YYSTYPE t = $2;
							if (t != NULL) {
								while (t->sibling != NULL) {
									t = t->sibling;
								}
								t->sibling = $3;
								$$ = $2;
							} else {
								$$ = $3;
							}
						}
						| LBRACE local-decl RBRACE {$$ = $2;}
						| LBRACE statement-lista RBRACE {$$ = $2;}
						| LBRACE RBRACE
						;

local-decl 				: local-decl var-decl {
							YYSTYPE t = $1;
							if (t != NULL) {
								while (t->sibling != NULL) {
									t = t->sibling;
								}
								t->sibling = $2;
								$$ = $1;
							} else {
								$$ = $2;
							}
						}
						| var-decl {$$ = $1;}
						;

statement-lista 		: statement-lista statement {
							YYSTYPE t = $1;
							if (t != NULL) {
								while (t->sibling != NULL) {
									t = t->sibling;
								}
								t->sibling = $2;
								$$ = $1;
							} else {
								$$ = $2;
							}
						}
						| statement {$$ = $1;}
						;

statement 				: expressao-decl {$$ = $1;}
						| composto-decl {$$ = $1;}
						| selecao-decl {$$ = $1;}
						| iteracao-decl {$$ = $1;}
						| retorno-decl{$$ = $1;}
						;

expressao-decl 			: expressao SEMI {$$ = $1;}
						| SEMI 
						;

selecao-decl 			: IF LPAREN expressao RPAREN statement {
							$$ = newStmtNode(IfK);
							$$->child[0] = $3;
							$$->child[1] = $5;
						}
						| IF LPAREN expressao RPAREN statement ELSE statement {
							$$ = newStmtNode(IfK);
							$$->child[0] = $3;
							$$->child[1] = $5;
							$$->child[2] = $7;
						}
						;

iteracao-decl 			: WHILE LPAREN expressao RPAREN statement {
							$$ = newStmtNode(WhileK);
							$$->child[0] = $3;
							$$->child[1] = $5;
						}
						;

retorno-decl 			: RETURN SEMI {
							$$ = newStmtNode(ReturnK);
						}
						| RETURN expressao SEMI {
							$$ = newStmtNode(ReturnK);
							$$->child[0] = $2;
						}
						;

expressao 				: var ASSIGN expressao {
							$$ = newExpNode(AtribK);
							$$->child[0] = $1;
							$$->child[1] = $3;
							$$->attr.op = ASSIGN;
						}
						| simples-expressao {$$ = $1;}
						;

var 					: id {
							$$ = $1;
						}
						| id LBRACKET expressao RBRACKET {
							$$ = $1;
							$$->child[0] = $3;
							$$->kind.exp = IdVectorK;
						}
						;

simples-expressao 		: soma-expressao relacional soma-expressao {
							$$ = $2;
							$$->child[0] = $1;
							$$->child[1] = $3;
						}
						| soma-expressao { $$ = $1;}
						;

relacional 				: LTEQ { 
							$$ = newExpNode(RelK);
							$$->attr.op = LTEQ;
						}
						| LT { 
							$$ = newExpNode(RelK);
							$$->attr.op = LT;
						}
						| GT { 
							$$ = newExpNode(RelK);
							$$->attr.op = GT;
						}
						| GTEQ { 
							$$ = newExpNode(RelK);
							$$->attr.op = GTEQ;
						}
						| EQ { 
							$$ = newExpNode(RelK);
							$$->attr.op = EQ;
						}
						| NEQ { 
							$$ = newExpNode(RelK);
							$$->attr.op = NEQ;
						}
						;

soma-expressao 			: soma-expressao soma termo {
							$$ = $2;
							$$->child[0] = $1;
							$$->child[1] = $3;
						}
						| termo { $$ = $1;}
						;

soma 					: PLUS { 
							$$ = newExpNode(OpK);
							$$->attr.op = PLUS;
						}
						| MINUS { 
							$$ = newExpNode(OpK);
							$$->attr.op = MINUS;
						}
						;

termo 					: termo mult fator {
							$$ = $2;
							$$->child[0] = $1;
							$$->child[1] = $3;
						}
						| fator {$$ = $1;}
						;

mult 					: TIMES { 
							$$ = newExpNode(OpK);
							$$->attr.op = TIMES;
						}
						| OVER { 
							$$ = newExpNode(OpK);
							$$->attr.op = OVER;
						}
						;

fator 					: LPAREN expressao RPAREN {$$ = $2;}
						| var { $$ = $1;}
						| ativacao { $$ = $1;}
						| num {$$ = $1;}
						;

ativacao 				: id LPAREN arg-lista RPAREN {
							$$ = $1;
							$$->kind.exp = CallK;
							$$->child[0] = $3;
						}
						| id LPAREN RPAREN {
							$$ = $1;
							$$->kind.exp = CallK;
						}
						;

arg-lista 				: arg-lista COMMA expressao {
							YYSTYPE t = $1;
							if (t != NULL) {
								while (t->sibling != NULL) {
									t = t->sibling;
								}
								t->sibling = $3;
								$$ = $1;
							} else {
								$$ = $3;
							}
						}
						| expressao {$$ = $1;}
						;

id						: ID {
							$$ = newExpNode(IdK);
							$$->attr.name = copyString(tokenString);
						}
						;

num						: NUM {
							$$ = newExpNode(LiteralK);
							$$->attr.val = atoi(tokenString);
						}
						;
%%

int yyerror(char * message)
{ 
	fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);
  	fprintf(listing,"Current token: ");
  	printToken(yychar,tokenString);
  	Error = TRUE;
  	return 0;
}

/* yylex calls getToken to make Yacc/Bison output
 * compatible with ealier versions of the TINY scanner
 */
static int yylex(void)
{ 
	return getToken(); 
}

TreeNode * parse(void)
{ 
	yyparse();
  	return savedTree;
}

