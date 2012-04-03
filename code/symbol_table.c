#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h" 

extern int main();
//~ symbol* sym_table=NULL;

char keywords[58][10]={"ARRAY" , "ASSIGNMENT" , "BREAK" , "BOR" , "BAND", "BNOT" , "CASE" , "CLASS" , "COMMA" , "COLON" , "CONST" , "CONTINUE" , "DO" , "DOT" , "DOWNTO" , "ELSE" , "END" , "EXIT" , "EXPORT" , "FOR" , "FUNCTION" , "GOTO" , "GTE" , "IF" , "IN" , "ISEQUAL" , "INTEGER" , "IS" , "LABEL" , "LTE" , "LT" , "MOD" , "NOT" , "NE" , "NUMBER" , "OR" , "OF" , "OPERATOR" , "PRIVATE" , "PROCEDURE", "PROGRAM" , "PUBLIC" , "RECORD" , "REAL" , "RANGE" , "REPEAT" , "STRING" , "SCOLON" , "THEN" , "TYPE" , "TO" , "VAR" , "WHILE" , "WITH" , "XOR" , "_BEGIN" , "_FALSE" , "_TRUE"};
int reserve[31]={0,2,6,12,15,19,21,100,23,100,100,28,31,32,35,38,100,42,46,48,100,51,52,54,100,100,100,100,100,100,55};


int lookup(char *key_name){
	printf("lookup :%s \n",key_name);
	int key;
	if(reserve[key_name[0]-'A']==100){ return 1;}
	else{
	//printf("")
	key=reserve[key_name[0]-'A'];
	printf("\nseraching for %s form %d\n",key_name,key);
	while((keywords[key][0]-key_name[0])==0)
	{	printf("current serach %s\n", keywords[key]);
		if(strcmp(keywords[key],key_name)==0){
			printf("Use of Identifer %s as identifer is not allowed\n",key_name);
			exit(1);
			}
		key=key+1;
	}
	return 1;
}
}

sym_table * ct_sym_table(sym_table *parent)
{
	sym_table *new_st;
	new_st = (sym_table *)malloc(sizeof(sym_table));
	new_st->parent = parent;
	new_st->head = NULL;
	printf("creating new symbol table \n");
	return new_st;
}

symbol * insert_sym(sym_table* st,char *sym_name)					// inserts symbol at the head of the sym_table
{
	symbol * ptr;
	ptr = (symbol*)malloc(sizeof(symbol)); //check for success of malloc
	if(ptr==NULL)
	{	
		printf("Memory Allocation fail: Symbol table ");
		exit(1);
	}
	ptr->name = strdup(sym_name);
	//if(st==NULL){st=ptr;ptr->next=NULL;}
	ptr->next = st->head;
	st->head = ptr;
	printf("inserted %s\n",sym_name);
	return ptr;
}

int setsymAttr(sym_table* st,char *sym_name, type_ value){  //
	symbol *ptr;
	ptr=find_sym(st,sym_name);
	ptr->nd_type = value;
	return 1;
}


symbol * find_sym(sym_table* st,char *sym_name)
{
	symbol *ptr;
	if(st==NULL){ptr=insert_sym(st,sym_name);}
	ptr = st->head;
	while(ptr!=NULL)
	{
		if(!strcmp(ptr->name,sym_name))
			return ptr;
		ptr= ptr->next;
	}
	return NULL;
}

