#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 6
# Christopher Llamas, chllamas
#
#       make                   	makes Order
#	make DictionaryTest  	makes DictionaryTest
#	make memcheck 		uses valgrind on Order
#	make memcheck2		uses valgrind on DictionaryTest
#	make clean		clears out files created by this Makefile
#------------------------------------------------------------------------------

CLIENT         	= Order
CLIENT2		= DictionaryTest
ADT            	= Dictionary
SOURCE         	= $(CLIENT).c
OBJECT         	= $(CLIENT).o
SOURCE2 	= $(CLIENT2).c
OBJECT2 	= $(CLIENT2).o
ADT_SOURCE     	= $(ADT).c
ADT_OBJECT     	= $(ADT).o
ADT_HEADER     	= $(ADT).h
COMPILE        	= gcc -c -std=c99 -Wall
LINK           	= gcc -o
REMOVE         	= rm -f
MEMCHECK       	= valgrind --leak-check=full

$(CLIENT) : $(OBJECT) $(ADT_OBJECT)
	$(LINK) $(CLIENT) $(OBJECT) $(ADT_OBJECT)

$(OBJECT) : $(SOURCE) $(ADT_HEADER)
	$(COMPILE) $(SOURCE)

$(CLIENT2) : $(OBJECT2) $(ADT_OBJECT)
	$(LINK) $(CLIENT2) $(OBJECT2) $(ADT_OBJECT)

$(OBJECT2) : $(SOURCE2) $(ADT_HEADER)
	$(COMPILE) $(SOURCE2)

$(ADT_OBJECT) : $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

clean :
	$(REMOVE) $(CLIENT) $(CLIENT2) $(OBJECT) $(OBJECT2) $(ADT_OBJECT)

memcheck : $(CLIENT)
	$(MEMCHECK) $(CLIENT) in out

memcheck2 : $(CLIENT2)
	$(MEMCHECK) $(CLIENT2)
