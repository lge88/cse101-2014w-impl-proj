CC = clang++

LIBRARIES +=
INCLUDE_PATHS += .

CFLAGS = -Wall -g -I$(INCLUDE_PATHS)
LDFLAGS = $(LIBRARIES)

all: testGraph testFindCC testFindMST testRandomGraph

%: %.cpp
	@$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

touch:
	touch -c *.cpp

clean:
	rm -fr $(OUT) *.dSYM *.o
