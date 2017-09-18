all : example1

lex.yy.c : example1.l
	flex example1.l

example1.tab.h example1.tab.c : example1.y
	bison -d -o example1.tab.c example1.y

example1 : lex.yy.c example1.tab.c example1.tab.h
	cc lex.yy.c example1.tab.c -o example1 -ll
