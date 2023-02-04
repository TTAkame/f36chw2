CC=g++
DEV=-Wall -Werror -g -std=c++14
OPT=-O3 -std=c++14

JSON=json.hpp

all: consistentresultverification sortedverification timealgorithms

consistentresultverification: consistentresultverification.cxx
	$(CC) $(DEV) consistentresultverification.cxx -o consistentresultverification

sortedverification: sortedverification.cxx
	$(CC) $(DEV) sortedverification.cxx -o sortedverification

timealgorithms: timealgorithms.cxx insertionsort.o mergesort.o quicksort.o
	$(CC) $(DEV) timealgorithms.cxx insertionsort.o mergesort.o quicksort.o -o timealgorithms

insertionsort.o: insertionsort.cpp insertionsort.h json.hpp
	$(CC) $(DEV) -c insertionsort.cpp

mergesort.o: mergesort.cpp mergesort.h json.hpp
	$(CC) $(DEV) -c mergesort.cpp

quicksort.o: quicksort.cpp quicksort.h json.hpp
	$(CC) $(DEV) -c quicksort.cpp

clean:
	rm -f *.o
	rm -rf *.dSYM
	rm -f consistentresultverification
	rm -f sortedverification
	rm -f timealgorithms
