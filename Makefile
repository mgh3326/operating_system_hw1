make:
	gcc -o a.out -g *.c validate.o
clean:
	rm -f *.o