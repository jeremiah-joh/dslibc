CC = cc
CFLAG = -Wall -ansi

test:
	$(CC) $(CFLAG) -o vec vec.c ../src/vec.h -g
	./vec
	$(CC) $(CFLAG) -o sll sll.c ../src/sll.h -g
	./sll
	$(CC) $(CFLAG) -o dll dll.c ../src/dll.h -g
	./dll
	$(CC) $(CFLAG) -o bst bst.c ../src/bst.h -g
	./bst
	$(CC) $(CFLAG) -o ht ht.c ../src/ht.h -g
	./ht
clean:
	rm -f vec sll dll bst ht
