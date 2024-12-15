CC = cc
CFLAGS = -ansi -Wall -Wextra -Wpedantic -Werror

all:
	$(CC) $(CFLAGS) -o vec vec.c -g
	./vec
	$(CC) $(CFLAGS) -o sll sll.c -g
	./sll
	$(CC) $(CFLAGS) -o dll dll.c -g
	./dll
	$(CC) $(CFLAGS) -o heap heap.c -g
	./heap
	$(CC) $(CFLAGS) -o ht ht.c -g
	./ht
	$(CC) $(CFLAGS) -o rbt rbt.c -g
	./rbt

clean:
	rm -f vec sll dll heap ht rbt
