CC = clang++
CFLAGS = -g -Wall
HEADERS = $(wildcard src/*.h)

all: test/run

test/run: test/main.cpp $(HEADERS)
	$(CC) $(CFLAGS) -Isrc -o $@ $<

check: test/run
	test/run

clean:
	rm -f test/run **/*.o
