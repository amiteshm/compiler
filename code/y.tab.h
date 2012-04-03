
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     AND = 258,
     ARRAY = 259,
     _BEGIN = 260,
     BREAK = 261,
     BOOLEAN = 262,
     CASE = 263,
     CLASS = 264,
     COMMA = 265,
     CONST = 266,
     CONTINUE = 267,
     DO = 268,
     DOWNTO = 269,
     ELSE = 270,
     END = 271,
     EXIT = 272,
     EXPORT = 273,
     _FALSE = 274,
     FOR = 275,
     FUNCTION = 276,
     POW = 277,
     GOTO = 278,
     IF = 279,
     IN = 280,
     INTEGER = 281,
     IS = 282,
     LABEL = 283,
     MOD = 284,
     NOT = 285,
     OR = 286,
     OF = 287,
     OPERATOR = 288,
     PRIVATE = 289,
     PROCEDURE = 290,
     PROGRAM = 291,
     PUBLIC = 292,
     RECORD = 293,
     REAL = 294,
     REPEAT = 295,
     STRING = 296,
     THEN = 297,
     REALNUM = 298,
     _TRUE = 299,
     TYPE = 300,
     TO = 301,
     VAR = 302,
     WHILE = 303,
     WITH = 304,
     XOR = 305,
     ISEQUAL = 306,
     NE = 307,
     GTE = 308,
     LT = 309,
     LTE = 310,
     ASSIGNMENT = 311,
     BOR = 312,
     BAND = 313,
     BNOT = 314,
     COLON = 315,
     SCOLON = 316,
     DOT = 317,
     RANGE = 318,
     INTNUM = 319,
     UNTIL = 320,
     IDENTIFIER = 321,
     IFX = 322,
     GT = 323,
     SUB = 324,
     ADD = 325,
     DIV = 326,
     MULT = 327,
     UMINUS = 328,
     PTR = 329
   };
#endif
/* Tokens.  */
#define AND 258
#define ARRAY 259
#define _BEGIN 260
#define BREAK 261
#define BOOLEAN 262
#define CASE 263
#define CLASS 264
#define COMMA 265
#define CONST 266
#define CONTINUE 267
#define DO 268
#define DOWNTO 269
#define ELSE 270
#define END 271
#define EXIT 272
#define EXPORT 273
#define _FALSE 274
#define FOR 275
#define FUNCTION 276
#define POW 277
#define GOTO 278
#define IF 279
#define IN 280
#define INTEGER 281
#define IS 282
#define LABEL 283
#define MOD 284
#define NOT 285
#define OR 286
#define OF 287
#define OPERATOR 288
#define PRIVATE 289
#define PROCEDURE 290
#define PROGRAM 291
#define PUBLIC 292
#define RECORD 293
#define REAL 294
#define REPEAT 295
#define STRING 296
#define THEN 297
#define REALNUM 298
#define _TRUE 299
#define TYPE 300
#define TO 301
#define VAR 302
#define WHILE 303
#define WITH 304
#define XOR 305
#define ISEQUAL 306
#define NE 307
#define GTE 308
#define LT 309
#define LTE 310
#define ASSIGNMENT 311
#define BOR 312
#define BAND 313
#define BNOT 314
#define COLON 315
#define SCOLON 316
#define DOT 317
#define RANGE 318
#define INTNUM 319
#define UNTIL 320
#define IDENTIFIER 321
#define IFX 322
#define GT 323
#define SUB 324
#define ADD 325
#define DIV 326
#define MULT 327
#define UMINUS 328
#define PTR 329




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 161 "parser.y"

	int int_val;
	double real_val;
	struct symbol* st_ptr;
	struct nodeTypeTag* nPtr;



/* Line 1676 of yacc.c  */
#line 209 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


