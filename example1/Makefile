CXXFLAGS=-std=gnu++11
all : example1

example1.lex.cpp : example1.l
	flex -o example1.lex.cpp example1.l
	sed -i- -e 's/register //g' example1.lex.cpp

example1.tab.hpp example1.tab.cpp : example1.ypp
	bison -d -o example1.tab.cpp example1.ypp

example1.lex.o : example1.lex.cpp example1.tab.hpp ast.hpp example1.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

ast.o : ast.cpp ast.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

generator.o : generator.cpp generator.hpp ast.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

example1.tab.o : example1.tab.cpp  ast.hpp example1.hpp generator.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

example1 : example1.tab.o example1.lex.o ast.o generator.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean :
	/bin/rm -rf \#* *~ *.o example1 example1.tab.cpp example1.tab.hpp example1.lex.cpp 

