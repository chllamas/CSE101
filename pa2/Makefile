#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 2
#
#       make                   	makes Arithmetic
#	make ListTest	       	makes ListTest
#	make BigIntegerTest  	makes BigIntegerTest
#	make clean		clears out files created by this Makefile
#------------------------------------------------------------------------------

Arithmetic : Arithmetic.o List.o BigInteger.o
	gcc -o Arithmetic Arithmetic.o List.o BigInteger.o

Arithmetic.o : Arithmetic.c List.c BigInteger.c
	gcc -c -std=c99 -Wall Arithmetic.c

BigIntegerTest : BigIntegerTest.o BigInteger.o List.o
	gcc -o BigIntegerTest BigIntegerTest.o BigInteger.o List.o

BigIntegerTest.o : BigIntegerTest.c List.c BigInteger.h List.h
	gcc -c -std=c99 -Wall BigIntegerTest.c

BigInteger.o : BigInteger.c BigInteger.h
	gcc -c -std=c99 -Wall BigInteger.c

ListTest : ListTest.o List.o
	gcc -o ListTest ListTest.o List.o

ListTest.o : ListTest.c List.h
	gcc -c -std=c99 -Wall ListTest.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

clean:
	rm -f Arithmetic ListTest BigIntegerTest Arithmetic.o ListTest.o List.o BigIntegerTest.o BigInteger.o
