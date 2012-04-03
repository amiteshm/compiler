#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "stack.h"
#include "symbol_table.h"

extern int main();
struct sym_table *myarray[100];

int top = 0;
void push(struct sym_table *ptr)
{
	if(top == 100)
	{
		printf("stack full cannot insert\n");
		exit(0);
	} 
	else
	{
		myarray[top] = ptr;
		top = top + 1;
		printf("push done %s\n",(ptr->head)->name);
	}
}

struct sym_table* pop()
{
	if (top != 0)
	{
		sym_table* ptr;
		ptr = (sym_table*)malloc(sizeof(sym_table));
		ptr = myarray[top];
		top = top - 1;
		return ptr;
	}
	else 
	{
		printf("stack empty cannot pop");
		return NULL;
	}
}
