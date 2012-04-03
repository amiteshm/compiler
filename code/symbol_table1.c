#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "symbol_table.h" 

extern int main();
symbol* sym_table=NULL;

my_sym_table * ct_sym_table(my_sym_table *parent)
{
	my_sym_table *new_st;
	new_st = (my_sym_table *)malloc(sizeof(my_sym_table));
	new_st -> parent = parent;
	printf("creating new symbol table");
	return new_st;
}

symbol * insert_sym(char *sym_name)
{
	symbol * ptr;
	ptr = (symbol*)malloc(sizeof(symbol));
	ptr->name = strdup(sym_name);
	ptr->next = sym_table;
	sym_table = ptr;
	return ptr;
}

symbol * find_sym(char *sym_name)
{
	symbol *ptr;
	ptr = sym_table;
	while(ptr!=NULL)
	{
		if(!strcmp(ptr->name,sym_name))
			return ptr;
		ptr= ptr->next;
	}
	return NULL;
}
