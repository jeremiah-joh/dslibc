include config.mk

HEADER = dll.h heap.h ht.h sll.h vec.h

all:
	@echo "usage: make check"
	@echo "       make clean"
	@echo "       make install"
	@echo "       make uninstall"

check:
	cd test && make

clean:
	cd test && make clean

install:
	mkdir -p $(PREFIX)/include
	cd src && cp $(HEADER) $(PREFIX)/include

uninstall:
	cd $(PREFIX)/include && rm $(HEADER)
