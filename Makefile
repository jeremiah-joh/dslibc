CC = cc
CFLAGS = -ansi -Wall -Wextra -Werror -g

test:
	$(CC) $(CFLAGS) tests/bst.c
	./a.out
	rm -f a.out
	$(CC) $(CFLAGS) tests/dll.c
	./a.out
	rm -f a.out
	$(CC) $(CFLAGS) tests/sll.c
	./a.out
	rm -f a.out
	$(CC) $(CFLAGS) tests/vec.c
	./a.out
	rm -f a.out
	$(CC) $(CFLAGS) tests/ht.c
	./a.out
	rm -f a.out
