CXXFLAGS=-O3 -Iinclude -std=c++11

all : bin/shapes

bin/shapes : src/shapes.cpp include/json.hpp
	if [ ! -d bin ] ; then mkdir bin; fi
	$(CXX) $(CXXFLAGS) -o $@ src/shapes.cpp $(LDFLAGS)
