include config.mk

HEADER = *.h

all:

install:
	mkdir -p "$(PREFIX)/include"
	cp src/$(HEADER) "$(PREFIX)/include"

uninstall:
	rm "$(PREFIX)/include/$(HEADER)"
