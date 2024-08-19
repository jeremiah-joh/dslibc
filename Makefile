CC = cc
CFLAGS = -ansi -Wall -Wextra -Wpedantic -Werror -g

all:
	@echo "Nothing to do"

test:
	$(CC) $(CFLAGS) -o bst tests/bst.c
	./bst
	$(CC) $(CFLAGS) -o dll tests/dll.c
	./dll
	$(CC) $(CFLAGS) -o sll tests/sll.c
	./sll
	$(CC) $(CFLAGS) -o vec tests/vec.c
	./vec
	$(CC) $(CFLAGS) -o ht tests/ht.c
	./ht
	$(CC) $(CFLAGS) -o heap tests/heap.c
	./heap

clean:
	rm bst dll sll vec ht heap
