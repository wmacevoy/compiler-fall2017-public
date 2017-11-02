VERSION=lib.macosx-10.12-intel-2.7

all : build/$(VERSION)/spam.so

build/$(VERSION)/spam.so : setup.py spammodule.c
	python setup.py build

test : build/$(VERSION)/spam.so testspam.py
	python testspam.py

install : ../lib/$(VERSION)/spam.so

../lib/$(VERSION)/spam.so : build/$(VERSION)/spam.so
	mkdir -p ../lib/$(VERSION)
	cp $< $@
