CC = clang++
# CC = g++

LIBRARIES +=
INCLUDE_PATHS += .

CFLAGS = -Wall -I$(INCLUDE_PATHS) -std=c++11 -O3
LDFLAGS = $(LIBRARIES)

EXES += testGraph
EXES += testFindMST
EXES += testFindCC
EXES += testRandomGraph
EXES += part1
#EXES += part1_2

all: $(EXES)

%: %.cpp
	$(CC) $(CFLAGS) $(LDLAGS) $< -o $@

testGraph: Graph.hpp Graph.algo.hpp
testFindMST: Graph.hpp Graph.algo.hpp
testFindCC: Graph.hpp Graph.algo.hpp
testRandomGraph: Graph.hpp Graph.algo.hpp
part1: Graph.hpp Graph.algo.hpp
part1_2: ListGraph.hpp part1_algorithms.hpp

touch:
	touch -c *.cpp

clean:
	rm -fr $(EXES) *.dSYM *.o
