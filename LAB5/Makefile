all: pi_serial.o pi_multithread.o code.o
	gcc -o code code.c -lpthread
	gcc -o pi_serial pi_serial.o
	gcc -o pi_multithread pi_multithread.c -lpthread
pi_serial.o:
	gcc -c pi_serial.c
pi_multithread.o:
	gcc -c pi_multithread.c 
code.o:
	gcc -c code.c
clean:
	rm *.o pi_multithread pi_serial code
