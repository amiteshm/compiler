%{
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


%}

%union
{
	int int_val;
	double real_val;
	struct symbol* st_ptr;
	struct nodeTypeTag* nPtr;
};

%token AND ARRAY _BEGIN BREAK BOOLEAN CASE CLASS COMMA CONST CONTINUE DO DOWNTO ELSE END EXIT EXPORT _FALSE FOR FUNCTION POW
%token GOTO IF IN INTEGER IS LABEL MOD NOT OR OF OPERATOR PRIVATE PROCEDURE PROGRAM PUBLIC RECORD REAL REPEAT STRING THEN REALNUM
%token _TRUE TYPE TO VAR WHILE WITH XOR ISEQUAL NE GTE LT LTE ASSIGNMENT BOR BAND BNOT '(' ')' '[' ']' COLON SCOLON DOT RANGE INTNUM UNTIL

%type <int_val> INTNUM
%type <real_val> REALNUM
%token <st_ptr> IDENTIFIER
%type <nPtr> stmt expr block program prog_heading id_list decl_part stmt_part var_decl_part func_decl_part var_decl_list var_decl 
%type <nPtr> type std_type array_type ptr_type  func_call term factor simple_expr actual_params expr_list
%type <nPtr> index_type_list stmt_seq assign_stmt if_stmt while_stmt compound_stmt func_heading param_list formal_param param_type


%nonassoc IFX
%nonassoc ELSE
%left GT GTE LT LTE ISEQUAL ASSIGNMENT 
%left ADD SUB OR
%left MULT DIV AND
%left NOT
%nonassoc UMINUS
%left PTR

%start program

%%
program : prog_heading block DOT    {$$=opr(DOT,2,$1,$2); } ;

prog_heading : PROGRAM IDENTIFIER {printf("ravi %s\n",yytext); symbol* entry=build_table(curr_st,yytext); entry->child_st = NULL; $2=entry;}
								  SCOLON {$$=opr(PROGRAM,1,id($2));}
	     | PROGRAM IDENTIFIER {symbol* entry=build_table(curr_st,yytext); entry->child_st = NULL; $2=entry;} 
								  '(' id_list ')' SCOLON  {$$=opr(PROGRAM,2,id($2),$5);}
	     ;
			 
id_list  : IDENTIFIER {printf("ravi34 %s\n",yytext); symbol* entry=build_table(curr_st,yytext); entry->child_st = NULL; $$ = id(entry);}
	     | id_list COMMA IDENTIFIER {printf("ravi43 %s\n",yytext); symbol* entry=build_table(curr_st,yytext); entry->child_st = NULL; $$ = opr(COMMA, 2, $1, id(entry));}
	     ;
			 
block 	     : decl_part stmt_part 
			 | decl_part;

decl_part    : var_decl_part func_decl_part ;

var_decl_part : VAR var_decl_list SCOLON {$$=$2;} ; 
	      

var_decl_list : var_decl_list SCOLON var_decl { $$ = opr(SCOLON, 2, $1, $3); }
	      | var_decl {$$=$1;}
	      ;
			  
var_decl  : id_list COLON type   {$$ = opr(COLON, 2, $1, $3);
				  traverse(curr_st,$1,$3->Type.myTYPE); /* change here too for traverse*/
					} ; 
type : std_type {$$=$1;}
	 | array_type  {$$=$1;}
	 | ptr_type  {$$=$1;}
	 ;

ptr_type  : PTR IDENTIFIER { symbol* entry=build_table(curr_st,yytext); entry->child_st = NULL; $$=opr(PTR,1,id(entry)); };

array_type : ARRAY '[' index_type_list ']' OF std_type {$$=opr(ARRAY,2,$3,$6);} ; 

index_type_list : INTNUM RANGE INTNUM {$$=opr(RANGE,2,icon($1),icon($3));}
				| index_type_list COMMA INTNUM RANGE INTNUM {/*rule for AST */}
				;

std_type  : INTEGER	{$$=type(tINT); /*chull */ } 
	      | REAL	{$$=type(tREAL);}
	      | BOOLEAN {$$=type(tBOOLEAN);}
	      ; 
	
stmt_part : _BEGIN stmt_seq  END	{ $$=$2 ;} ; 

stmt_seq : stmt_seq stmt SCOLON { $$ = opr(SCOLON, 2, $1, $2); }
		 | stmt SCOLON {$$=$1;}
		 ;

stmt : assign_stmt {$$=$1;}
	 | if_stmt {$$=$1; }
	 | while_stmt {$$=$1;} 
	 | compound_stmt {$$=$1;}
	 ;
	  
assign_stmt	: IDENTIFIER {symbol* entry=find_sym(curr_st,yytext); entry->child_st = NULL; if (entry == NULL)
														{/*error function*/ yyerror("varibale undefined at "); /*give line number}*/}
														 else{ node=id(entry);} }
													 ASSIGNMENT expr {  $$ = opr(ASSIGNMENT,2,node, $4); if(type_check(node,$4))
																										{$$->abs_type=$4->abs_type;}
													  else{yyerror("Type not match in Assignment"); $$->abs_type=tERROR;}} ;

if_stmt : IF '(' expr ')' THEN _BEGIN stmt_seq END %prec IFX  	{ $$ = opr(IF, 2, $3, $7); 
													 if($3->abs_type!=tBOOLEAN)
													 {yyerror("condition inside if is not boolean"); 
														$$->abs_type=tERROR;} }
		| IF '(' expr ')' THEN _BEGIN stmt_seq END ELSE _BEGIN stmt_seq END  { $$ = opr(IF, 3, $3, $7, $11);
																				if($3->abs_type!=tBOOLEAN)
																				{yyerror("condition inside if is not boolean");
																				 $$->abs_type=tERROR;} }
		;

while_stmt : WHILE '(' expr ')' DO _BEGIN stmt END { $$ = opr(WHILE, 2, $3, $7); 
														if($3->abs_type!=tBOOLEAN)
														{yyerror("condition inside while is not boolean");
														 $$->abs_type=tERROR;}  } ;       

compound_stmt : _BEGIN stmt_seq END {$$=$2;};

expr : simple_expr						{ $$ = $1; }
	 | simple_expr LT simple_expr		{ $$ = opr(LT,2,$1,$3); $$->abs_type=tBOOLEAN;}
	 | simple_expr LTE simple_expr		{ $$ = opr(LTE,2,$1,$3); $$->abs_type=tBOOLEAN;}
	 | simple_expr GT simple_expr		{ $$ = opr(GT,2,$1,$3); $$->abs_type=tBOOLEAN;}
	 | simple_expr GTE simple_expr		{ $$ = opr(GTE,2,$1,$3); $$->abs_type=tBOOLEAN;}
	 | simple_expr ISEQUAL simple_expr	{ $$ = opr(ISEQUAL,2,$1,$3); $$->abs_type=tBOOLEAN;}
	 | simple_expr NE simple_expr		{ $$ = opr(NE,2,$1,$3); $$->abs_type=tBOOLEAN;}
	 ;

simple_expr : term					{ $$ = $1; }
			| simple_expr ADD term	{ $$ = opr(ADD,2,$1,$3); if(type_check($1,$3))
																{$$->abs_type=$1->abs_type;} 
																else{yyerror("Type not match in Addition ");$$->abs_type=tERROR;}}
			| simple_expr SUB term	{ $$ = opr(SUB,2,$1,$3); if(type_check($1,$3))
																{$$->abs_type=$1->abs_type;} 
																else{yyerror("Type not match in Sub ");$$->abs_type=tERROR;}}
			| simple_expr OR term	{ $$ = opr(OR,2,$1,$3); if($1->abs_type==tBOOLEAN && $3->abs_type==tBOOLEAN )
																{$$->abs_type=tBOOLEAN;}
																else {yyerror("OR is not defind for the given expr");
																$$->abs_type=tERROR;}}
			;
			
term : factor						{ $$ = $1; }
	 | term MULT factor				{ $$ = opr(MULT,2,$1,$3); if($1->abs_type==tREAL){
																	if($3->abs_type==tREAL||$3->abs_type==tINT)
																		{$$->abs_type=tREAL;}
																	else{yyerror("type error");$$->abs_type=tERROR;}}
																else if($3->abs_type==tREAL){
																	if($1->abs_type==tREAL||$1->abs_type==tINT)
																		{$$->abs_type=tREAL;}
																	else{yyerror("type error in mult");$$->abs_type=tERROR;}}
																else if($1->abs_type == tINT && $3->abs_type == tINT )
																	{$$->abs_type=tINT;}}
	 | term DIV factor				{ $$ = opr(DIV,2,$1,$3); if($1->abs_type==$3->abs_type)
															{$$->abs_type=$1->abs_type;}}
	 | term AND factor				{ $$ = opr(AND,2,$1,$3); if($1->abs_type==tBOOLEAN && $3->abs_type==tBOOLEAN )
																{$$->abs_type=tBOOLEAN;}
																else {yyerror("AND is not defind for the given expr");
																$$->abs_type=tERROR;}}
	 ;
	 
factor : INTNUM						{ $$ = icon($1); }
	   | REALNUM					{ $$ = rcon($1); }
	   | IDENTIFIER					{ symbol* entry=find_sym(curr_st,yytext); entry->child_st = NULL; if (entry == NULL)
									{/*error function*/	yyerror("varibale undefined at ");}/*give line number*/ 
									else{$$ = id(entry);}}
	   | NOT factor					{ $$ = opr(NOT, 1, $2); if($2->abs_type==tBOOLEAN )
																{$$->abs_type=tBOOLEAN;}
																else {yyerror("NOT is not defined for the given expr");
																$$->abs_type=tERROR;}}
	   | '(' expr ')'				{ $$ = $2; }
	   | _TRUE						{ $$ = type(tBOOLEAN); $$->abs_type=tBOOLEAN;}
	   | _FALSE						{ $$ = type(tBOOLEAN); $$->abs_type=tBOOLEAN;}
	   | SUB factor %prec UMINUS	{ $$ = opr(UMINUS, 1, $2); }
	   ;
	   
func_decl_part : func_decl_list SCOLON
			   |
			   ;

func_decl_list : func_decl_list SCOLON func_decl
			   | func_decl
			   ;

func_decl : func_heading SCOLON block { curr_st=pop(); } ; 

func_heading : FUNCTION IDENTIFIER {symbol* entry=build_table(curr_st,yytext); push(curr_st); curr_st = ct_sym_table(curr_st); 
										entry->child_st = curr_st;} '(' param_list ')' COLON type
			 | FUNCTION IDENTIFIER {symbol* entry=build_table(curr_st,yytext); push(curr_st); curr_st = ct_sym_table(curr_st); 
										entry->child_st = curr_st;} COLON type
			 ;
			 
param_list : formal_param {$$ = $1;}
		   | param_list SCOLON formal_param  { $$ = opr(SCOLON, 2, $1, $3); }
		   ;
		   
formal_param : id_list COLON param_type				{ $$ = opr(COLON, 2, $1, $3); }
			 | id_list COLON ARRAY OF param_type	{ $$ = opr(COLON, 2, $1, $5); }
			 ;

param_type : REAL		{ $$=type(tREAL); }
		   | INTEGER	{ $$=type(tINT); }
		   ;

func_call : IDENTIFIER {symbol* entry=find_sym(curr_st,yytext); if(entry == NULL)
																{yyerror("undeclared function name");}
																else {push(curr_st);
																if(entry->child_st != NULL)
																	  curr_st = entry->child_st;
																else yyerror("error in function calling");}	} actual_params ;

actual_params : '(' expr_list ')' { $$ = $2; } ;	

expr_list : expr
		  | expr_list COMMA expr  {$$ = opr(COMMA, 2, $1, $3);}
		  ;

%%

int main()
{	if (curr_st == NULL)
			{printf("first symbol table created\n");
				curr_st = ct_sym_table(curr_st);
							  }		
	yyparse();
	printf ("Parsing Completed\n");
	return 0;
}
