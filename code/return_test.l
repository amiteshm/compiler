%{
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "y.tab.h"
#include "parser.h"
#include "symbol_table.h"
extern YYSTYPE yylval;
extern char* yytext;
int yyline_no = 1;
int yycolumn=1;
void yyerror (char *);
%}
tab 		[ \t]
space 		{tab}+
comment1 	"//".*\n
comment2 	\{[^\}]*\}
comment3 	\(\*[^\*\)]*\*\)
letter 		[A-Za-z_]
digit 		[0-9]
id 			{letter}({letter}|{digit})*
int_num		{digit}+
real_num 	{digit}+(\.{digit}+)?(E[-+]?{digit}+)?

%%

{comment1} 	{/*no action*/}
{comment2} 	{/*no action*/}
{comment3} 	{/*no action*/}
{space}		{yycolumn=yycolumn+yyleng; }
\n			{yycolumn=1; yyline_no++;  }
and 		{yycolumn=yycolumn+yyleng;return (AND);} 
array 		{yycolumn=yycolumn+yyleng;return (ARRAY);}
begin 		{yycolumn=yycolumn+yyleng;return (_BEGIN);}
break		{yycolumn=yycolumn+yyleng;return (BREAK);}
boolean|Boolean		{yycolumn=yycolumn+yyleng;return (BOOLEAN);}
case 		{yycolumn=yycolumn+yyleng;return (CASE);}
class 		{yycolumn=yycolumn+yyleng;return (CLASS);}
const 		{yycolumn=yycolumn+yyleng; return (CONST);}
continue	{yycolumn=yycolumn+yyleng; return (CONTINUE);}
div 		{yycolumn=yycolumn+yyleng; return (DIV);}
do 			{yycolumn=yycolumn+yyleng; return (DO);}
downto 		{yycolumn=yycolumn+yyleng; return (DOWNTO);}
else 		{yycolumn=yycolumn+yyleng; return (ELSE);}
end 		{yycolumn=yycolumn+yyleng; return (END);}
exit 		{yycolumn=yycolumn+yyleng; return (EXIT);}
export 		{yycolumn=yycolumn+yyleng; return (EXPORT);}
false 		{yycolumn=yycolumn+yyleng; return (_FALSE);}
for 		{yycolumn=yycolumn+yyleng; return (FOR);}
function 	{yycolumn=yycolumn+yyleng; return (FUNCTION);}
goto 		{yycolumn=yycolumn+yyleng; return (GOTO);}
if 			{yycolumn=yycolumn+yyleng; return (IF);}
in 			{yycolumn=yycolumn+yyleng; return (IN);}
integer|Integer	{yycolumn=yycolumn+yyleng; return (INTEGER);}
is 			{yycolumn=yycolumn+yyleng; return (IS);}
label 		{yycolumn=yycolumn+yyleng; return (LABEL);}
mod 		{yycolumn=yycolumn+yyleng; return (MOD);}
not 		{yycolumn=yycolumn+yyleng; return (NOT);}
of 			{yycolumn=yycolumn+yyleng; return (OF);}
operator	{yycolumn=yycolumn+yyleng; return (OPERATOR);}
or 			{yycolumn=yycolumn+yyleng; return (OR);}
pow 		{yycolumn=yycolumn+yyleng; return (POW);}
private 	{yycolumn=yycolumn+yyleng; return (PRIVATE);}
procedure 	{yycolumn=yycolumn+yyleng; return (PROCEDURE);}
program 	{yycolumn=yycolumn+yyleng; return (PROGRAM);}
public 		{yycolumn=yycolumn+yyleng; return (PUBLIC);}
record 		{yycolumn=yycolumn+yyleng; return (RECORD);}
repeat 		{yycolumn=yycolumn+yyleng; return (REPEAT);}
real|Real	{yycolumn=yycolumn+yyleng; return (REAL);}
string 		{yycolumn=yycolumn+yyleng; return (STRING);}
then 		{yycolumn=yycolumn+yyleng; return (THEN);}
to 			{yycolumn=yycolumn+yyleng; return (TO);}
true		{yycolumn=yycolumn+yyleng; return(_TRUE);}
type|Type 	{yycolumn=yycolumn+yyleng; return (TYPE);}
until 		{yycolumn=yycolumn+yyleng; return (UNTIL);}
var 		{yycolumn=yycolumn+yyleng; return (VAR);}
while 		{yycolumn=yycolumn+yyleng; return (WHILE);}
with 		{yycolumn=yycolumn+yyleng; return (WITH);}
xor 		{yycolumn=yycolumn+yyleng; return (XOR);}
"+"			{yycolumn=yycolumn+yyleng; return (ADD);}
"\^"		{yycolumn=yycolumn+yyleng; return (PTR);}
"-"			{yycolumn=yycolumn+yyleng; return (SUB);}
"*"			{yycolumn=yycolumn+yyleng; return (MULT);}
"="			{yycolumn=yycolumn+yyleng; return (ISEQUAL);}
"<>"		{yycolumn=yycolumn+yyleng; return (NE);}
">"			{yycolumn=yycolumn+yyleng; return (GT);}
"<"			{yycolumn=yycolumn+yyleng; return (LT);}
">="		{yycolumn=yycolumn+yyleng; return (GTE);}
"<="		{yycolumn=yycolumn+yyleng; return (LTE);}
":="		{yycolumn=yycolumn+yyleng; return (ASSIGNMENT);}
"~"			{yycolumn=yycolumn+yyleng; return (BNOT);}
"&"			{yycolumn=yycolumn+yyleng;return (BAND);}
"\|" 		{yycolumn=yycolumn+yyleng; return (BOR);}
\(			{yycolumn=yycolumn+yyleng; return '(';}
\)			{yycolumn=yycolumn+yyleng; return ')';}
":"			{yycolumn=yycolumn+yyleng; return (COLON);}
";"			{yycolumn=yycolumn+yyleng; return (SCOLON);}
","			{yycolumn=yycolumn+yyleng; return (COMMA);}
"\.\."		{yycolumn=yycolumn+yyleng; return (RANGE);}
"\["		{yycolumn=yycolumn+yyleng; return '[';}
"\]"		{yycolumn=yycolumn+yyleng; return ']';}
"\."		{yycolumn=yycolumn+yyleng; return (DOT);}
{int_num} 	{yycolumn=yycolumn+yyleng; yylval.int_val = atoi(yytext);
							return INTNUM;}
{real_num} 	{yycolumn=yycolumn+yyleng; yylval.real_val = atoi(yytext);
							return REALNUM;}
{id} 		{yycolumn=yycolumn+yyleng; return IDENTIFIER;} 

%%
int yywrap()
{
	return 1;
}
