CC = cc

all:
	$(CC) -o vec vec.c -g
	./vec
	$(CC) -o sll sll.c -g
	./sll
	$(CC) -o dll dll.c -g
	./dll
	$(CC) -o heap heap.c -g
	./heap
	$(CC) -o ht ht.c -g
	./ht
	$(CC) -O0 -o rbt rbt.c -g
	./rbt

clean:
	rm -f vec sll dll heap ht rbt
