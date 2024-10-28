include config.mk

HEADER = avl.h bst.h bt.h dll.h heap.h ht.h rbt.h sll.h spt.h vec.h

all:
	@echo "usage: make install"
	@echo "       make uninstall"

install:
	mkdir -p $(PREFIX)/include
	cd src && cp $(HEADER) $(PREFIX)/include

uninstall:
	cd $(PREFIX)/include && rm $(HEADER)
