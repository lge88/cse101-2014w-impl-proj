# CC = clang++
CC = g++

LIBRARIES +=
INCLUDE_PATHS += .

CFLAGS = -Wall -g -I$(INCLUDE_PATHS) -std=c++11
LDFLAGS = $(LIBRARIES)

all: testGraph testFindCC testFindMST testRandomGraph part1

%: %.cpp
	@$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

touch:
	touch -c *.cpp

clean:
	rm -fr $(OUT) *.dSYM *.o
