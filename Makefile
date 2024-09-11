CC = cc

all:
	$(CC) -o vec test/vec.c -g
	./vec
	$(CC) -o sll test/sll.c -g
	./sll
	$(CC) -o dll test/dll.c -g
	./dll
	$(CC) -o heap test/heap.c -g
	./heap
	$(CC) -o ht test/ht.c -g
	./ht

clean:
	rm -f vec sll dll heap ht
