#Makefile for baseConversion.
#
#Compiler: GCC

CC=gcc -Wall

all: baseConversion

baseConversion: conversionOps.o errors.o stringOps.o conversionOps.h errors.h stringOps.h baseConversion.h baseConversion.c
	$(CC) -o baseConversion baseConversion.c conversionOps.o errors.o stringOps.o

conversionOps.o: conversionOps.h conversionOps.c 
	$(CC) -c conversionOps.c 

stringOps.o: stringOps.h stringOps.c
	$(CC) -c stringOps.c 

errors.o: errors.h errors.c
	$(CC) -c errors.c

clean: 
	rm -f baseConversion *.o 
tidy: 
	rm -f *.o 
