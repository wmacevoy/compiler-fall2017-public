PY2=/usr/bin/python

all:
	$(MAKE) -C rand all
	$(MAKE) -C spam all

install:
	$(MAKE) -C rand install
	$(MAKE) -C spam install

test:
	$(MAKE) -C rand test
	$(PY2) src/userand.py
	$(MAKE) -C spam test
	$(PY2) src/usespam.py

run:	install
	$(PY2) src/shapes.py
	$(PY2) src/fastshapes.py


shapes : shapes.cpp
	$(CXX) -std=c++11 -O -o $@ $<

