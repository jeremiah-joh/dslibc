include config.mk

HEADER = dll.h heap.h ht.h sll.h vec.h

all:
	@echo "usage: make install"
	@echo "       make uninstall"

install:
	mkdir -p $(PREFIX)/include
	cd src && cp $(HEADER) $(PREFIX)/include

uninstall:
	cd $(PREFIX)/include && rm $(HEADER)
