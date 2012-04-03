all: test

test: lex.yy.c y.tab.c symbol_table.c symbol_table.h stack.c stack.h
	cc -o test -g lex.yy.c  y.tab.c symbol_table.c stack.c -lfl

y.tab.c : parser.y symbol_table.c stack.c
	yacc -vd parser.y

lex.yy.c: return_test.l symbol_table.c
	flex return_test.l
	
clean:
	rm -rf *.o y.tab.* lex.yy.c test  

