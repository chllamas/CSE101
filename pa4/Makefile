#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 4
# Christopher Llamas, chllamas
#
#       make                   	makes FindComponents
#	make GraphTest  	makes GraphTest
#	make memcheck 		uses valgrind on FindComponents
#				*must have input file named "in" in same directory*
# 	make memcheck2		uses valgrind on GraphTest
#	make clean		clears out files created by this Makefile
#------------------------------------------------------------------------------

CLIENT         	= FindComponents
CLIENT2		= GraphTest
ADT            	= Graph
ADT2		= List
SOURCE         	= $(CLIENT).c
OBJECT         	= $(CLIENT).o
SOURCE2 	= $(CLIENT2).c
OBJECT2 	= $(CLIENT2).o
ADT_SOURCE     	= $(ADT).c
ADT_OBJECT     	= $(ADT).o
ADT_HEADER     	= $(ADT).h
ADT2_SOURCE	= $(ADT2).c
ADT2_OBJECT     = $(ADT2).o
ADT2_HEADER     = $(ADT2).h
COMPILE        	= gcc -c -std=c99 -Wall
LINK           	= gcc -o
REMOVE         	= rm -f
MEMCHECK       	= valgrind --leak-check=full

$(CLIENT) : $(OBJECT) $(ADT_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(CLIENT) $(OBJECT) $(ADT_OBJECT) $(ADT2_OBJECT)

$(OBJECT) : $(SOURCE) $(ADT_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(SOURCE)

$(CLIENT2) : $(OBJECT2) $(ADT_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(CLIENT2) $(OBJECT2) $(ADT_OBJECT) $(ADT2_OBJECT)

$(OBJECT2) : $(SOURCE2) $(ADT_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(SOURCE2)

$(ADT_OBJECT) : $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

$(ADT2_OBJECT) : $(ADT2_SOURCE) $(ADT2_HEADER)
	$(COMPILE) $(ADT2_SOURCE)

clean :
	$(REMOVE) $(CLIENT) $(CLIENT2) $(OBJECT) $(OBJECT2) $(ADT_OBJECT) $(ADT2_OBJECT)

memcheck : $(CLIENT)
	$(MEMCHECK) $(CLIENT) in out

memcheck2 : $(CLIENT2)
	$(MEMCHECK) $(CLIENT2)
