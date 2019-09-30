all: pi_multithread.o
	gcc -o pi_multithread pi_multithread.o -lpthread
pi_multithread.o:
	gcc -c pi_multithread.c
clean:
	rm *.o pi_multithread