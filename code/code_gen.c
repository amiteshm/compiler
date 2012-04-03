#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int temp_count = 1;
int label_count = 1;
char buffer[256] = {0};
char buffer1[256] = {0};

char *newtemp()
{
	char a = 't';
	bzero(buffer,256);
	sprintf(buffer,"%c%d",a,temp_count);
	temp_count = temp_count + 1;
	return buffer;
}

char *newlabel()
{
	char b = 'L';
	bzero(buffer,256);
	sprintf(buffer,"%c%d",b,label_count);
	label_count = label_count + 1;
	return buffer;
}

char *gen_binary_op(struct nodeTypeTag* res,struct nodeTypeTag* a,struct nodeTypeTag* opcode,struct nodeTypeTag* b)
{
	if (opcode->opr.oper == ADD)
	{
		bzero(buffer,256);
		bzero(buffer1,256);
		res->place = newtemp();
		strcat(buffer,a->code);
		strcat(buffer,b->code);
		sprintf(buffer1,"%s %s %s %s %s",res->place,":=",a->place,"+",b->place);
		strcat(buffer,buffer1);
		return buffer;
	}
	else if (opcode->opr.oper == SUB)
	{
		bzero(buffer,256);
		bzero(buffer1,256);
		res->place = newtemp();
		strcat(buffer,a->code);
		strcat(buffer,b->code);
		sprintf(buffer1,"%s %s %s %s %s",res->place,":=",a->place,"-",b->place);
		strcat(buffer,buffer1);
		return buffer;
	}
	else if (opcode->opr.oper == MULT)
	{
		bzero(buffer,256);
		bzero(buffer1,256);
		res->place = newtemp();
		strcat(buffer,a->code);
		strcat(buffer,b->code);
		sprintf(buffer1,"%s %s %s %s %s",res->place,":=",a->place,"*",b->place);
		strcat(buffer,buffer1);
		return buffer;
	}
	else if (opcode->opr.oper == DIV)
	{
		bzero(buffer,256);
		bzero(buffer1,256);
		res->place = newtemp();
		strcat(buffer,a->code);
		strcat(buffer,b->code);
		sprintf(buffer1,"%s %s %s %s %s",res->place,":=",a->place,"/",b->place);
		strcat(buffer,buffer1);
		return buffer;
	}	
}


int main()
{
	int i;
	char *temp,*label;
	for (i=0;i<5;i++)
	{
		temp = newtemp();
		printf("%s\n",temp);
		label = newlabel();
		printf("%s\n",label);
	}
}
