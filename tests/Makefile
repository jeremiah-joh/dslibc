CC = cc
CFLAG = -Wall -ansi

check:
	$(CC) $(CFLAG) *.c
	rm -f a.out
test:
	$(CC) $(CFLAG) -o vec *.c -g
	./vec
