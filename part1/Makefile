CC = clang++
# CC = g++

LIBRARIES +=
INCLUDE_PATHS += .

CFLAGS = -Wall -g -I$(INCLUDE_PATHS) -std=c++11
LDFLAGS = $(LIBRARIES)

EXES += testGraph
EXES += testFindMST
EXES += testFindCC
EXES += testRandomGraph
EXES += part1

all: $(EXES)

%: %.cpp
	$(CC) $(LDLAGS) $< -o $@

testGraph: Graph.hpp Graph.algo.hpp
testFindMST: Graph.hpp Graph.algo.hpp
testFindCC: Graph.hpp Graph.algo.hpp
testRandomGraph: Graph.hpp Graph.algo.hpp
part1: Graph.hpp Graph.algo.hpp

touch:
	touch -c *.cpp

clean:
	rm -fr $(EXES) *.dSYM *.o
