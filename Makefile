CFLAG = -Wall -ansi

check:
	cc $(CFLAG) *.c
debug:
	cc $(CFLAG) -o debug *.c -g
clean:
	rm -f a.out debug *.gch
