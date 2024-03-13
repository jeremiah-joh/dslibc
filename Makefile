CFLAG = -Wall -ansi

check:
	cc $(CFLAG) *.c
	rm -f a.out
clean:
	rm -f a.out debug *.gch
test:
	cc $(CFLAG) -o debug *.c -g
	./debug
	rm -f debug
