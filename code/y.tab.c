
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <stdarg.h>
#include <ctype.h> 
#include "symbol_table.h" 
#include "parser.h"
#include "stack.h"
#define YYDEBUG 1 
extern int yylex();
extern char* yytext;
extern int yywrap();
extern int yyline_no;
extern int yycolumn;
extern int yyleng;
struct sym_table *curr_st;
struct nodeTypeTag *node;
void yyerror (char *s) /* Called by yyparse on error */
{
	printf ("%d:%d:error:%s at %s  \n",yyline_no,yycolumn-yyleng,s,yytext);
}

//traversal function
// edit here too for scoping

void traverse(struct sym_table *curr_st,struct nodeTypeTag* root,type_ Value){
	int i;
	if(root->type==typeId){setsymAttr(curr_st,root->id.ptr->name,Value); root->abs_type=Value; }
	else if (root->type==typeRcon || root->type==typeIcon){;}
	else{
		for(i=0;i< root->opr.nops;i++){
			traverse(curr_st,root->opr.op[i],Value);
		}
	}
}

/*build_table builds symbol table by inserting the token symbols into the list if not found on searching at first*/	
symbol* build_table(sym_table *curr_st,char *sym_name)					
{ 
	symbol * s;
	s = find_sym(curr_st,sym_name);
	if (s == NULL)
	{
		s = insert_sym(curr_st,sym_name);
		return s;
	}
	else 
	{ 	//should flag an error	
		return s;
	}
}
/*context_check(char *sym_name)
{ 
	if (insert_sym(sym_name) == 0)
	printf("%s is an undeclared identiﬁer\n", sym_name);
}*/

nodeType *icon(int value) {
    nodeType *p;

    /* allocate node */
    if ((p = malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeIcon;
    p->abs_type=tINT;
    p->icon.nops=0;
    p->icon.value = value;

    return p;
}

nodeType *rcon(double value) {
    nodeType *p;

    /* allocate node */
    if ((p = malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeRcon;
    p->abs_type=tREAL;
    p->rcon.nops=0;
    p->rcon.value = value;

    return p;
}

nodeType *type(type_ TYPE) {
    nodeType *p;

    /* allocate node */
    if ((p = malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeType;
    p->Type.myTYPE = TYPE;

    return p;
}

int type_check(struct nodeTypeTag* S,struct nodeTypeTag* T){
		type_ S_type,T_type;
		S_type=S->abs_type;
		T_type=T->abs_type;
		if(S_type==T_type){return 1;}
		else {return 0;}
}

nodeType *id(symbol * ptr) {
    nodeType *p;
	/*symbol* entry=find_sym(name);
	if (entry == NULL)
	{
		// error function
		yyerror("varibale undefined at ");			// give line number
	}*/
	
    /* allocate node */
    if ((p = malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeId;
    p->abs_type=ptr->nd_type;
    p->id.nops=0;
    p->id.ptr = ptr;

    return p;
}

nodeType *opr(int oper, int nops, ...) {
    va_list ap;
    nodeType *p;
    int i;
	
    /* allocate node */
    if ((p = malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");
    if ((p->opr.op = malloc(nops * sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeOpr;
    p->opr.oper = oper;
    p->opr.nops = nops;
    va_start(ap, nops);
    for (i = 0; i < nops; i++)
        p->opr.op[i] = va_arg(ap, nodeType*);
    va_end(ap);
    return p;
}




/* Line 189 of yacc.c  */
#line 233 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 214 of yacc.c  */
#line 161 "parser.y"

	int int_val;
	double real_val;
	struct symbol* st_ptr;
	struct nodeTypeTag* nPtr;



/* Line 214 of yacc.c  */
#line 426 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 438 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   157

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  79
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNRULES -- Number of states.  */
#define YYNSTATES  157

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   329

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      60,    61,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    62,     2,    63,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,     8,    13,    14,    22,    24,    28,
      31,    33,    36,    40,    44,    46,    50,    52,    54,    56,
      59,    66,    70,    76,    78,    80,    82,    86,    90,    93,
      95,    97,    99,   101,   102,   107,   116,   129,   138,   142,
     144,   148,   152,   156,   160,   164,   168,   170,   174,   178,
     182,   184,   188,   192,   196,   198,   200,   202,   205,   209,
     211,   213,   216,   219,   220,   224,   226,   230,   231,   240,
     241,   247,   249,   253,   257,   263,   265
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      80,     0,    -1,    81,    85,    66,    -1,    -1,    36,    70,
      82,    65,    -1,    -1,    36,    70,    83,    60,    84,    61,
      65,    -1,    70,    -1,    84,    10,    70,    -1,    86,    95,
      -1,    86,    -1,    87,   107,    -1,    47,    88,    65,    -1,
      88,    65,    89,    -1,    89,    -1,    84,    64,    90,    -1,
      94,    -1,    92,    -1,    91,    -1,    78,    70,    -1,     4,
      62,    93,    63,    32,    94,    -1,    68,    67,    68,    -1,
      93,    10,    68,    67,    68,    -1,    26,    -1,    39,    -1,
       7,    -1,     5,    96,    16,    -1,    96,    97,    65,    -1,
      97,    65,    -1,    98,    -1,   100,    -1,   101,    -1,   102,
      -1,    -1,    70,    99,    56,   103,    -1,    24,    60,   103,
      61,    42,     5,    96,    16,    -1,    24,    60,   103,    61,
      42,     5,    96,    16,    15,     5,    96,    16,    -1,    48,
      60,   103,    61,    13,     5,    97,    16,    -1,     5,    96,
      16,    -1,   104,    -1,   104,    54,   104,    -1,   104,    55,
     104,    -1,   104,    72,   104,    -1,   104,    53,   104,    -1,
     104,    51,   104,    -1,   104,    52,   104,    -1,   105,    -1,
     104,    74,   105,    -1,   104,    73,   105,    -1,   104,    31,
     105,    -1,   106,    -1,   105,    76,   106,    -1,   105,    75,
     106,    -1,   105,     3,   106,    -1,    68,    -1,    43,    -1,
      70,    -1,    30,   106,    -1,    60,   103,    61,    -1,    44,
      -1,    19,    -1,    73,   106,    -1,   108,    65,    -1,    -1,
     108,    65,   109,    -1,   109,    -1,   110,    65,    85,    -1,
      -1,    21,    70,   111,    60,   113,    61,    64,    90,    -1,
      -1,    21,    70,   112,    64,    90,    -1,   114,    -1,   113,
      65,   114,    -1,    84,    64,   115,    -1,    84,    64,     4,
      32,   115,    -1,    39,    -1,    26,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   192,   192,   194,   194,   196,   196,   200,   201,   204,
     205,   207,   209,   212,   213,   216,   219,   220,   221,   224,
     226,   228,   229,   232,   233,   234,   237,   239,   240,   243,
     244,   245,   246,   249,   249,   256,   260,   266,   271,   273,
     274,   275,   276,   277,   278,   279,   282,   283,   286,   289,
     295,   296,   306,   308,   314,   315,   316,   319,   323,   324,
     325,   326,   329,   330,   333,   334,   337,   339,   339,   341,
     341,   345,   346,   349,   350,   353,   354
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "AND", "ARRAY", "_BEGIN", "BREAK",
  "BOOLEAN", "CASE", "CLASS", "COMMA", "CONST", "CONTINUE", "DO", "DOWNTO",
  "ELSE", "END", "EXIT", "EXPORT", "_FALSE", "FOR", "FUNCTION", "POW",
  "GOTO", "IF", "IN", "INTEGER", "IS", "LABEL", "MOD", "NOT", "OR", "OF",
  "OPERATOR", "PRIVATE", "PROCEDURE", "PROGRAM", "PUBLIC", "RECORD",
  "REAL", "REPEAT", "STRING", "THEN", "REALNUM", "_TRUE", "TYPE", "TO",
  "VAR", "WHILE", "WITH", "XOR", "ISEQUAL", "NE", "GTE", "LT", "LTE",
  "ASSIGNMENT", "BOR", "BAND", "BNOT", "'('", "')'", "'['", "']'", "COLON",
  "SCOLON", "DOT", "RANGE", "INTNUM", "UNTIL", "IDENTIFIER", "IFX", "GT",
  "SUB", "ADD", "DIV", "MULT", "UMINUS", "PTR", "$accept", "program",
  "prog_heading", "$@1", "$@2", "id_list", "block", "decl_part",
  "var_decl_part", "var_decl_list", "var_decl", "type", "ptr_type",
  "array_type", "index_type_list", "std_type", "stmt_part", "stmt_seq",
  "stmt", "assign_stmt", "$@3", "if_stmt", "while_stmt", "compound_stmt",
  "expr", "simple_expr", "term", "factor", "func_decl_part",
  "func_decl_list", "func_decl", "func_heading", "$@4", "$@5",
  "param_list", "formal_param", "param_type", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
      40,    41,    91,    93,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    79,    80,    82,    81,    83,    81,    84,    84,    85,
      85,    86,    87,    88,    88,    89,    90,    90,    90,    91,
      92,    93,    93,    94,    94,    94,    95,    96,    96,    97,
      97,    97,    97,    99,    98,   100,   100,   101,   102,   103,
     103,   103,   103,   103,   103,   103,   104,   104,   104,   104,
     105,   105,   105,   105,   106,   106,   106,   106,   106,   106,
     106,   106,   107,   107,   108,   108,   109,   111,   110,   112,
     110,   113,   113,   114,   114,   115,   115
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     0,     4,     0,     7,     1,     3,     2,
       1,     2,     3,     3,     1,     3,     1,     1,     1,     2,
       6,     3,     5,     1,     1,     1,     3,     3,     2,     1,
       1,     1,     1,     0,     4,     8,    12,     8,     3,     1,
       3,     3,     3,     3,     3,     3,     1,     3,     3,     3,
       1,     3,     3,     3,     1,     1,     1,     2,     3,     1,
       1,     2,     2,     0,     3,     1,     3,     0,     8,     0,
       5,     1,     3,     3,     5,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     3,     1,     0,     0,    10,    63,
       0,     0,     7,     0,     0,    14,     2,     0,     9,     0,
      11,     0,    65,     0,     4,     0,     0,     0,    12,     0,
       0,     0,    33,     0,     0,    29,    30,    31,    32,    67,
      62,     0,     0,     8,     0,    25,    23,    24,     0,    15,
      18,    17,    16,    13,     0,     0,     0,     0,    26,     0,
      28,     0,     0,    64,    66,     0,     0,    19,    38,    60,
       0,    55,    59,     0,    54,    56,     0,     0,    39,    46,
      50,     0,     0,    27,     0,     0,     6,     0,     0,    57,
       0,    61,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,     0,     0,    71,
      70,     0,     0,     0,    58,     0,    49,    44,    45,    43,
      40,    41,    42,    48,    47,    53,    52,    51,     0,     0,
       0,     0,    21,     0,     0,     0,     0,     0,    76,    75,
      73,     0,    72,     0,    20,     0,     0,     0,    68,    22,
      35,    37,    74,     0,     0,     0,    36
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    10,    11,    13,     7,     8,     9,    14,
      15,    49,    50,    51,    88,    52,    18,    33,    34,    35,
      57,    36,    37,    38,    77,    78,    79,    80,    20,    21,
      22,    23,    61,    62,   108,   109,   140
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -77
static const yytype_int16 yypact[] =
{
     -13,   -57,    32,   -12,   -26,   -77,   -21,   -25,    47,    36,
       9,    18,   -77,    -6,    20,   -77,   -77,     6,   -77,    -3,
     -77,    28,   -77,    30,   -77,   -21,    26,    -1,   -21,     6,
      23,    38,   -77,     0,    34,   -77,   -77,   -77,   -77,    -5,
      36,   -12,     2,   -77,    19,   -77,   -77,   -77,    27,   -77,
     -77,   -77,   -77,   -77,     3,    -4,    -4,    45,   -77,    40,
     -77,    42,    39,   -77,   -77,    57,    44,   -77,   -77,   -77,
      -4,   -77,   -77,    -4,   -77,   -77,    -4,    63,    37,     4,
     -77,    68,    -4,   -77,   -21,    -1,   -77,    64,    21,   -77,
      69,   -77,    90,    -4,    -4,    -4,    -4,    -4,    -4,    -4,
      -4,    -4,    -4,    -4,    -4,   120,   -77,     8,   -18,   -77,
     -77,    66,    67,   104,   -77,   132,     4,    13,    13,    13,
      13,    13,    13,     4,     4,   -77,   -77,   -77,   133,    16,
      75,   -21,   -77,    73,     7,     6,     6,   109,   -77,   -77,
     -77,    -1,   -77,    74,   -77,     5,   127,    11,   -77,   -77,
     129,   -77,   -77,   140,     6,    12,   -77
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -77,   -77,   -77,   -77,   -77,   -23,   105,   -77,   -77,   -77,
     119,   -76,   -77,   -77,   -77,    15,   -77,   -29,   -32,   -77,
     -77,   -77,   -77,   -77,   -11,    22,    14,    24,   -77,   -77,
     108,   -77,   -77,   -77,   -77,    25,    10
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -70
static const yytype_int16 yytable[] =
{
      54,    59,    42,    44,    26,    29,    45,   102,    29,   110,
      29,    29,    26,     4,    45,    69,    58,    29,    26,    68,
     137,   150,    59,     1,    30,    46,    70,    30,   156,    30,
      30,   112,     5,    46,    -5,     6,    30,   138,    47,    71,
      72,    16,   138,   130,    93,    81,    47,   131,    31,    12,
     139,    31,    17,    31,    31,   139,    73,    19,    27,   -69,
      31,   107,    90,    65,    74,   148,    75,    39,    93,    76,
      32,   106,   129,    32,    24,    32,    32,    48,    25,   103,
     104,    66,    32,    55,   113,    28,   100,   101,    94,    95,
      96,    97,    98,    40,    89,    41,    43,    67,    56,    60,
      91,    82,    84,    85,   146,    83,   145,   116,   107,    99,
     100,   101,    87,    59,   123,   124,   117,   118,   119,   120,
     121,   122,    86,    59,    92,   155,   125,   126,   127,   105,
     114,   111,   115,   128,   132,   133,   134,   135,   136,   141,
     143,   147,   149,   151,   153,   154,    64,    53,    63,   144,
       0,     0,     0,     0,     0,     0,   142,   152
};

static const yytype_int16 yycheck[] =
{
      29,    33,    25,     4,    10,     5,     7,     3,     5,    85,
       5,     5,    10,    70,     7,    19,    16,     5,    10,    16,
       4,    16,    54,    36,    24,    26,    30,    24,    16,    24,
      24,    10,     0,    26,    60,    47,    24,    26,    39,    43,
      44,    66,    26,    61,    31,    56,    39,    65,    48,    70,
      39,    48,     5,    48,    48,    39,    60,    21,    64,    64,
      48,    84,    73,    61,    68,   141,    70,    70,    31,    73,
      70,    82,    64,    70,    65,    70,    70,    78,    60,    75,
      76,    62,    70,    60,    63,    65,    73,    74,    51,    52,
      53,    54,    55,    65,    70,    65,    70,    70,    60,    65,
      76,    56,    60,    64,   136,    65,   135,    93,   131,    72,
      73,    74,    68,   145,   100,   101,    94,    95,    96,    97,
      98,    99,    65,   155,    61,   154,   102,   103,   104,    61,
      61,    67,    42,    13,    68,    68,    32,     5,     5,    64,
      67,    32,    68,    16,    15,     5,    41,    28,    40,   134,
      -1,    -1,    -1,    -1,    -1,    -1,   131,   147
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    36,    80,    81,    70,     0,    47,    85,    86,    87,
      82,    83,    70,    84,    88,    89,    66,     5,    95,    21,
     107,   108,   109,   110,    65,    60,    10,    64,    65,     5,
      24,    48,    70,    96,    97,    98,   100,   101,   102,    70,
      65,    65,    84,    70,     4,     7,    26,    39,    78,    90,
      91,    92,    94,    89,    96,    60,    60,    99,    16,    97,
      65,   111,   112,   109,    85,    61,    62,    70,    16,    19,
      30,    43,    44,    60,    68,    70,    73,   103,   104,   105,
     106,   103,    56,    65,    60,    64,    65,    68,    93,   106,
     103,   106,    61,    31,    51,    52,    53,    54,    55,    72,
      73,    74,     3,    75,    76,    61,   103,    84,   113,   114,
      90,    67,    10,    63,    61,    42,   105,   104,   104,   104,
     104,   104,   104,   105,   105,   106,   106,   106,    13,    64,
      61,    65,    68,    68,    32,     5,     5,     4,    26,    39,
     115,    64,   114,    67,    94,    96,    97,    32,    90,    68,
      16,    16,   115,    15,     5,    96,    16
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 192 "parser.y"
    {(yyval.nPtr)=opr(DOT,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(2) - (3)].nPtr)); }
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 194 "parser.y"
    {printf("ravi %s\n",yytext); symbol* entry=build_table(curr_st,yytext); entry->child_st = NULL; (yyvsp[(2) - (2)].st_ptr)=entry; printf("ravitest %s\n",(yyvsp[(2) - (2)].st_ptr)->name);}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 195 "parser.y"
    {(yyval.nPtr)=opr(PROGRAM,1,id((yyvsp[(2) - (4)].st_ptr)));}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 196 "parser.y"
    {symbol* entry=build_table(curr_st,yytext); entry->child_st = NULL; (yyvsp[(2) - (2)].st_ptr)=entry;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 197 "parser.y"
    {(yyval.nPtr)=opr(PROGRAM,2,id((yyvsp[(2) - (7)].st_ptr)),(yyvsp[(5) - (7)].nPtr));}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 200 "parser.y"
    {printf("ravi34 %s\n",yytext); symbol* entry=build_table(curr_st,yytext); entry->child_st = NULL; (yyval.nPtr) = id(entry);}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 201 "parser.y"
    {printf("ravi43 %s\n",yytext); symbol* entry=build_table(curr_st,yytext); entry->child_st = NULL; (yyval.nPtr) = opr(COMMA, 2, (yyvsp[(1) - (3)].nPtr), id(entry));}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 209 "parser.y"
    {(yyval.nPtr)=(yyvsp[(2) - (3)].nPtr);}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 212 "parser.y"
    { (yyval.nPtr) = opr(SCOLON, 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr)); }
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 213 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 216 "parser.y"
    {(yyval.nPtr) = opr(COLON, 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr));
				  traverse(curr_st,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr)->Type.myTYPE); /* change here too for traverse*/
					}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 219 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 220 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 221 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 224 "parser.y"
    { symbol* entry=build_table(curr_st,yytext); entry->child_st = NULL; (yyval.nPtr)=opr(PTR,1,id(entry)); }
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 226 "parser.y"
    {(yyval.nPtr)=opr(ARRAY,2,(yyvsp[(3) - (6)].nPtr),(yyvsp[(6) - (6)].nPtr));}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 228 "parser.y"
    {(yyval.nPtr)=opr(RANGE,2,icon((yyvsp[(1) - (3)].int_val)),icon((yyvsp[(3) - (3)].int_val)));}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 229 "parser.y"
    {/*rule for AST */}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 232 "parser.y"
    {(yyval.nPtr)=type(tINT); /*chull */ }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 233 "parser.y"
    {(yyval.nPtr)=type(tREAL);}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 234 "parser.y"
    {(yyval.nPtr)=type(tBOOLEAN);}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 237 "parser.y"
    { (yyval.nPtr)=(yyvsp[(2) - (3)].nPtr) ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 239 "parser.y"
    { (yyval.nPtr) = opr(SCOLON, 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(2) - (3)].nPtr)); }
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 240 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (2)].nPtr);}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 243 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 244 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr); }
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 245 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 246 "parser.y"
    {(yyval.nPtr)=(yyvsp[(1) - (1)].nPtr);}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 249 "parser.y"
    {symbol* entry=find_sym(curr_st,yytext); entry->child_st = NULL; if (entry == NULL)
														{/*error function*/ yyerror("varibale undefined at "); /*give line number}*/}
														 else{ node=id(entry);} }
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 252 "parser.y"
    {  (yyval.nPtr) = opr(ASSIGNMENT,2,node, (yyvsp[(4) - (4)].nPtr)); if(type_check(node,(yyvsp[(4) - (4)].nPtr)))
																										{(yyval.nPtr)->abs_type=(yyvsp[(4) - (4)].nPtr)->abs_type;}
													  else{yyerror("Type not match in Assignment"); (yyval.nPtr)->abs_type=tERROR;}}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 256 "parser.y"
    { (yyval.nPtr) = opr(IF, 2, (yyvsp[(3) - (8)].nPtr), (yyvsp[(7) - (8)].nPtr)); 
													 if((yyvsp[(3) - (8)].nPtr)->abs_type!=tBOOLEAN)
													 {yyerror("condition inside if is not boolean"); 
														(yyval.nPtr)->abs_type=tERROR;} }
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 260 "parser.y"
    { (yyval.nPtr) = opr(IF, 3, (yyvsp[(3) - (12)].nPtr), (yyvsp[(7) - (12)].nPtr), (yyvsp[(11) - (12)].nPtr));
																				if((yyvsp[(3) - (12)].nPtr)->abs_type!=tBOOLEAN)
																				{yyerror("condition inside if is not boolean");
																				 (yyval.nPtr)->abs_type=tERROR;} }
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 266 "parser.y"
    { (yyval.nPtr) = opr(WHILE, 2, (yyvsp[(3) - (8)].nPtr), (yyvsp[(7) - (8)].nPtr)); 
														if((yyvsp[(3) - (8)].nPtr)->abs_type!=tBOOLEAN)
														{yyerror("condition inside while is not boolean");
														 (yyval.nPtr)->abs_type=tERROR;}  }
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 271 "parser.y"
    {(yyval.nPtr)=(yyvsp[(2) - (3)].nPtr);}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 273 "parser.y"
    { (yyval.nPtr) = (yyvsp[(1) - (1)].nPtr); }
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 274 "parser.y"
    { (yyval.nPtr) = opr(LT,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr)); (yyval.nPtr)->abs_type=tBOOLEAN;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 275 "parser.y"
    { (yyval.nPtr) = opr(LTE,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr)); (yyval.nPtr)->abs_type=tBOOLEAN;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 276 "parser.y"
    { (yyval.nPtr) = opr(GT,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr)); (yyval.nPtr)->abs_type=tBOOLEAN;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 277 "parser.y"
    { (yyval.nPtr) = opr(GTE,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr)); (yyval.nPtr)->abs_type=tBOOLEAN;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 278 "parser.y"
    { (yyval.nPtr) = opr(ISEQUAL,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr)); (yyval.nPtr)->abs_type=tBOOLEAN;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 279 "parser.y"
    { (yyval.nPtr) = opr(NE,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr)); (yyval.nPtr)->abs_type=tBOOLEAN;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 282 "parser.y"
    { (yyval.nPtr) = (yyvsp[(1) - (1)].nPtr); }
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 283 "parser.y"
    { (yyval.nPtr) = opr(ADD,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr)); if(type_check((yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr)))
																{(yyval.nPtr)->abs_type=(yyvsp[(1) - (3)].nPtr)->abs_type;} 
																else{yyerror("Type not match in Addition ");(yyval.nPtr)->abs_type=tERROR;}}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 286 "parser.y"
    { (yyval.nPtr) = opr(SUB,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr)); if(type_check((yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr)))
																{(yyval.nPtr)->abs_type=(yyvsp[(1) - (3)].nPtr)->abs_type;} 
																else{yyerror("Type not match in Sub ");(yyval.nPtr)->abs_type=tERROR;}}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 289 "parser.y"
    { (yyval.nPtr) = opr(OR,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr)); if((yyvsp[(1) - (3)].nPtr)->abs_type==tBOOLEAN && (yyvsp[(3) - (3)].nPtr)->abs_type==tBOOLEAN )
																{(yyval.nPtr)->abs_type=tBOOLEAN;}
																else {yyerror("OR is not defind for the given expr");
																(yyval.nPtr)->abs_type=tERROR;}}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 295 "parser.y"
    { (yyval.nPtr) = (yyvsp[(1) - (1)].nPtr); }
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 296 "parser.y"
    { (yyval.nPtr) = opr(MULT,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr)); if((yyvsp[(1) - (3)].nPtr)->abs_type==tREAL){
																	if((yyvsp[(3) - (3)].nPtr)->abs_type==tREAL||(yyvsp[(3) - (3)].nPtr)->abs_type==tINT)
																		{(yyval.nPtr)->abs_type=tREAL;}
																	else{yyerror("type error");(yyval.nPtr)->abs_type=tERROR;}}
																else if((yyvsp[(3) - (3)].nPtr)->abs_type==tREAL){
																	if((yyvsp[(1) - (3)].nPtr)->abs_type==tREAL||(yyvsp[(1) - (3)].nPtr)->abs_type==tINT)
																		{(yyval.nPtr)->abs_type=tREAL;}
																	else{yyerror("type error in mult");(yyval.nPtr)->abs_type=tERROR;}}
																else if((yyvsp[(1) - (3)].nPtr)->abs_type == tINT && (yyvsp[(3) - (3)].nPtr)->abs_type == tINT )
																	{(yyval.nPtr)->abs_type=tINT;}}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 306 "parser.y"
    { (yyval.nPtr) = opr(DIV,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr)); if((yyvsp[(1) - (3)].nPtr)->abs_type==(yyvsp[(3) - (3)].nPtr)->abs_type)
															{(yyval.nPtr)->abs_type=(yyvsp[(1) - (3)].nPtr)->abs_type;}}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 308 "parser.y"
    { (yyval.nPtr) = opr(AND,2,(yyvsp[(1) - (3)].nPtr),(yyvsp[(3) - (3)].nPtr)); if((yyvsp[(1) - (3)].nPtr)->abs_type==tBOOLEAN && (yyvsp[(3) - (3)].nPtr)->abs_type==tBOOLEAN )
																{(yyval.nPtr)->abs_type=tBOOLEAN;}
																else {yyerror("AND is not defind for the given expr");
																(yyval.nPtr)->abs_type=tERROR;}}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 314 "parser.y"
    { (yyval.nPtr) = icon((yyvsp[(1) - (1)].int_val)); }
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 315 "parser.y"
    { (yyval.nPtr) = rcon((yyvsp[(1) - (1)].real_val)); }
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 316 "parser.y"
    { symbol* entry=find_sym(curr_st,yytext); entry->child_st = NULL; if (entry == NULL)
									{/*error function*/	yyerror("varibale undefined at ");}/*give line number*/ 
									else{(yyval.nPtr) = id(entry);}}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 319 "parser.y"
    { (yyval.nPtr) = opr(NOT, 1, (yyvsp[(2) - (2)].nPtr)); if((yyvsp[(2) - (2)].nPtr)->abs_type==tBOOLEAN )
																{(yyval.nPtr)->abs_type=tBOOLEAN;}
																else {yyerror("NOT is not defined for the given expr");
																(yyval.nPtr)->abs_type=tERROR;}}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 323 "parser.y"
    { (yyval.nPtr) = (yyvsp[(2) - (3)].nPtr); }
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 324 "parser.y"
    { (yyval.nPtr) = type(tBOOLEAN); (yyval.nPtr)->abs_type=tBOOLEAN;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 325 "parser.y"
    { (yyval.nPtr) = type(tBOOLEAN); (yyval.nPtr)->abs_type=tBOOLEAN;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 326 "parser.y"
    { (yyval.nPtr) = opr(UMINUS, 1, (yyvsp[(2) - (2)].nPtr)); }
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 337 "parser.y"
    { curr_st=pop(); }
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 339 "parser.y"
    {symbol* entry=build_table(curr_st,yytext); push(curr_st); curr_st = ct_sym_table(curr_st); 
										entry->child_st = curr_st;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 341 "parser.y"
    {symbol* entry=build_table(curr_st,yytext); push(curr_st); curr_st = ct_sym_table(curr_st); 
										entry->child_st = curr_st;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 345 "parser.y"
    {(yyval.nPtr) = (yyvsp[(1) - (1)].nPtr);}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 346 "parser.y"
    { (yyval.nPtr) = opr(SCOLON, 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr)); }
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 349 "parser.y"
    { (yyval.nPtr) = opr(COLON, 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr)); }
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 350 "parser.y"
    { (yyval.nPtr) = opr(COLON, 2, (yyvsp[(1) - (5)].nPtr), (yyvsp[(5) - (5)].nPtr)); }
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 353 "parser.y"
    { (yyval.nPtr)=type(tREAL); }
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 354 "parser.y"
    { (yyval.nPtr)=type(tINT); }
    break;



/* Line 1455 of yacc.c  */
#line 2283 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 370 "parser.y"


int main()
{	if (curr_st == NULL)
			{printf("first symbol table created\n");
				curr_st = ct_sym_table(curr_st);
							  }		
	yyparse();
	printf ("Parsing Completed\n");
	return 0;
}

