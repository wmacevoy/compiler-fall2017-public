CXXFLAGS=-std=gnu++11 -Iinclude
all : dirs bin/hvac tests

dirs : tmp bin
	if [ ! -d tmp ] ; then mkdir tmp; fi
	if [ ! -d bin ] ; then mkdir bin; fi

tmp/hvac.lex.cpp : src/hvac.l
	flex -o tmp/hvac.lex.cpp src/hvac.l
	sed -i- -e 's/register //g' tmp/hvac.lex.cpp

tmp/hvac.tab.hpp tmp/hvac.tab.cpp : src/hvac.ypp
	bison -d -o tmp/hvac.tab.cpp src/hvac.ypp

tmp/hvac.lex.o : tmp/hvac.lex.cpp tmp/hvac.tab.hpp include/ast.hpp include/hvac.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tmp/ast.o : src/ast.cpp include/ast.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tmp/generator.o : src/generator.cpp include/generator.hpp include/ast.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

tmp/hvac.tab.o : tmp/hvac.tab.cpp  include/ast.hpp include/hvac.hpp include/generator.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

bin/hvac : tmp/hvac.tab.o tmp/hvac.lex.o tmp/ast.o tmp/generator.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean :
	/bin/rm -rf \#* *~ *.o hvac hvac.tab.cpp hvac.tab.hpp hvac.lex.cpp hvac.lex.cpp- tests/*.out tmp/*

.PHONY: tests
tests: bin/hvac
	c=1; while [ -f tests/hvac.$$c.in  ]; do if [ tests/hvac.$$c.out -ot tests/hvac.$$c.in -o tests/hvac.$$c.out -ot bin/hvac ] ; then ./bin/hvac < tests/hvac.$$c.in > tests/hvac.$$c.out ; fi ; c=$$(($$c+1)); done
