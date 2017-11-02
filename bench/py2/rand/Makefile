VERSION=lib.macosx-10.12-intel-2.7

all : build/$(VERSION)/rand.so

build/$(VERSION)/rand.so : setup.py randmodule.c
	python setup.py build

test : build/$(VERSION)/rand.so testrand.py
	python testrand.py

install : ../lib/$(VERSION)/rand.so

../lib/$(VERSION)/rand.so : build/$(VERSION)/rand.so
	mkdir -p ../lib/$(VERSION)
	cp $< $@
