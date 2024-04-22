CC = cc
CFLAGS = -Wall -ansi

test:
	$(CC) $(CFLAGS) -o tests/vec tests/vec.c src/vec.h -g
	./tests/vec
	$(CC) $(CFLAGS) -o tests/sll tests/sll.c src/sll.h -g
	./tests/sll
	$(CC) $(CFLAGS) -o tests/dll tests/dll.c src/dll.h -g
	./tests/dll
	$(CC) $(CFLAGS) -o tests/bst tests/bst.c src/bst.h -g
	./tests/bst
	$(CC) $(CFLAGS) -o tests/avl tests/avl.c src/avl.h -g
	./tests/avl
	$(CC) $(CFLAGS) -o tests/rbt tests/rbt.c src/rbt.h -g
	./tests/rbt
	$(CC) $(CFLAGS) -o tests/ht tests/ht.c src/ht.h -g
	./tests/ht
clean:
	rm -f tests/vec tests/sll tests/dll tests/bst tests/avl tests/rbt tests/ht
