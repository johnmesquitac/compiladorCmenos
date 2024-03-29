/****************************************************/
/* File: tiny.l                                     */
/* Lex specification for TINY                       */
/* Compiler Construction: Principles and Practice   */

%{
#include "globals.h"
#include "util.h"
#include "scan.h"
/* lexeme of identifier or reserved word */
char tokenString[MAXTOKENLEN+1];
static int yylex(void);
%}

digit       [0-9]
number      {digit}+
letter      [a-zA-Z_]
identifier  {letter}+
newline     [\n]
whitespace  [ \t\r]+

%%

"if"            {return IF;}
"else"          {return ELSE;}/**/
"int"           {return INT;}/**/
"return"        {return RETURN;}/**/
"void"         	{return VOID;}/**/
"while"         {return WHILE;}/**/
"="            	{return ASSIGN;}
"!="            {return NEQ;}/**/
"=="            {return EQ;}
"<"             {return LT;}
"<="            {return LTEQ;}/**/
">"             {return GT;}/**/
">="            {return GTEQ;}/**/
"+"             {return PLUS;}
"-"             {return MINUS;}
"*"             {return TIMES;}
"/"             {return OVER;}
";"             {return SEMI;}
","             {return COMMA;}/**/
"("             {return LPAREN;}
")"             {return RPAREN;}
"["             {return LBRACKET;}/**/
"]"             {return RBRACKET;}/**/
"{"             {return LBRACE;}/**/
"}"             {return RBRACE;}/**/

{number}        {return NUM;}
{identifier}    {return ID;}
{newline}       {lineno++;}
{whitespace}    {/* skip whitespace */}

"/*"             { char c = ' '; char anterior; 
                  do
                  { 
			anterior = c;
			c = input();
                    	if (c == EOF) return ERROR;
			if (c == '\n') lineno++;
                  } while (c != '/' || anterior != '*');
                }
.               {return ERROR;}

%%

TokenType getToken(void)
{ static int firstTime = TRUE;
  TokenType currentToken;
  if (firstTime)
  { firstTime = FALSE;
    lineno++;
    yyin = source;
    yyout = listing;
  }
  currentToken = yylex();
  strncpy(tokenString,yytext,MAXTOKENLEN);
  if (TraceScan) {
    fprintf(listing,"\t%d: ",lineno);
    printToken(currentToken,tokenString);
  }
  return currentToken;
}

