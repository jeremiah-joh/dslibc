CC = cc

all:
	$(CC) -o vec test/vec.c -g
	./vec

clean:
	rm -f vec
