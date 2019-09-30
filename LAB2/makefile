all: main.o factorial.o readline.o
	gcc main.o factorial.o readline.o -o factorial

main.o: main.c factorial.h readline.h
	gcc -c main.c

factorial.o: factorial.c factorial.h
	gcc -c factorial.c

readline.o: readline.c readline.h
	gcc -c readline.c

clean:
	rm -f *.o factorial

