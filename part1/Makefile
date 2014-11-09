CC = gcc
CXX = g++

INCLUDES =
CFLAGS	= -g -Wall $(INCLUDES)
CXXFLAGS	= -g -Wall $(INCLUDES)

LDFLAGS = -g
LDLIBS = -lmylist

.PHONY: default
default: mdb-add mdb-lookup libmylist.a

libmylist.a: mylist.o
	ar rc libmylist.a mylist.o
	ranlib libmylist.a


mdb-add: mdb-add.o mdb.o

mdb-lookup: mdb.o mdb-lookup.o

mdb.o: mdb.c mdb.h

mdb-add.o: mdb-add.c mdb.h

mdb-lookup.o: mdb-lookup.c mdb.h


.PHONY: clean
clean:
	rm -f *.o *~ mdb-lookup mdb-add

.PHONY: all
all: clean main

.PHONY: lookup
lookup: all
	valgrind --track-origins=yes --leak-check=full ./mdb-lookup mdb-cs3157

.PHONY: add
add: all 
	valgrind --track-origins=yes --leak-check=full ./mdb-add mdb-cs3157
	
