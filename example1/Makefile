all : example1

example1.lex.cpp : example1.l
	flex -o example1.lex.cpp example1.l

example1.tab.hpp example1.tab.cpp : example1.ypp
	bison -d -o example1.tab.cpp example1.ypp

example1 : lex.yy.cpp example1.tab.cpp example1.tab.h
	c++ lex.yy.cpp example1.tab.c -o example1 -ll

