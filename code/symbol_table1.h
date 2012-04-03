#ifndef symbol_table_h_included
#define symbol_table_h_included

#include "parser.h"
typedef enum {
	tINT, tCHAR, tDOUBLE, tBOOLEAN, tVOID, tERROR, tINTARRAY, tCHARARRAY, tREAL
	}type_;

struct my_sym_table{
	struct my_sym_table *parent;	// pointer to the parent symbol table
	struct symbol *head;			// pointer to the head sym of the curr symbol table
	int depth;						// function calling depth
};
typedef struct my_sym_table my_sym_table;

struct symbol
{
	char *name;				//token value field to be made
	type_ nd_type; 
	struct symbol *next;
};
typedef struct symbol symbol;

my_sym_table* ct_sym_table(my_sym_table* parent);
symbol * insert_sym(char *sym_name);
symbol * find_sym(char *sym_name);

#endif
