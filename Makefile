CC = cc

all:
	$(CC) -o vec test/vec.c -g
	./vec
	$(CC) -o sll test/sll.c -g
	./sll
	$(CC) -o dll test/dll.c -g
	./dll

clean:
	rm -f vec sll dll
