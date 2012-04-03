#ifndef symbol_table_h_included
#define symbol_table_h_included

typedef enum type_{
	tINT, tCHAR, tBOOLEAN, tVOID, tERROR, tINTARRAY, tCHARARRAY, tREAL
	}type_;

//ravi change
typedef struct symbol symbol;
typedef struct sym_table sym_table;

struct sym_table{
	struct sym_table *parent;		// pointer to the parent symbol table
	struct symbol *head;			// pointer to the head sym of the curr symbol table
	//~ int depth;						// function calling depth
};
//ravi change

struct symbol
{
	char *name;				//token value field to be made
	type_ nd_type; 
	int if_fn_name;				// takes value equal to 1 when symbol inserted is a function name 0 otherwise and ravi 
	struct sym_table *child_st; // pointer to the child symbol table if if_fn_name = 1 for that symbol NULL otherwise and ravi
	struct symbol *next;
};

symbol * insert_sym(sym_table* st,char *sym_name);
symbol * find_sym(sym_table* st,char *sym_name);
int lookup(char *key_name);
sym_table* ct_sym_table(sym_table* parent);     //ravi change
#endif
