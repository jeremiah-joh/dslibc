CC = cc

all:
	$(CC) -o vec test/vec.c -g
	./vec
	$(CC) -o sll test/sll.c -g
	./sll

clean:
	rm -f vec sll
