include config.mk

HEADER = dll.h heap.h ht.h sll.h vec.h

all: help

help:
	@echo "usage: make help"
	@echo "       make dist"
	@echo "       make check"
	@echo "       make clean"
	@echo "       make install"
	@echo "       make uninstall"

dist: clean
	mkdir -p dslibc-$(VERSION)
	cp -r LICENSE Makefile README.md config.mk\
		doc/ src/ test/ dslibc-$(VERSION)
	tar -cf - dslibc-$(VERSION) | gzip > dslibc-$(VERSION).tar.gz
	rm -rf dslibc-$(VERSION)

check:
	cd test && make

clean:
	cd test && make clean

install:
	mkdir -p $(PREFIX)/include
	cd src && cp $(HEADER) $(PREFIX)/include

uninstall:
	cd $(PREFIX)/include && rm $(HEADER)
