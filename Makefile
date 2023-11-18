CC = clang++
CFLAGS = -g -Wall
HEADERS = $(wildcard src/*.h)

all: run-tests

run-tests: test/main.cpp $(HEADERS)
	$(CC) $(CFLAGS) -Isrc -o $@ $<

check: run-tests
	./run-tests

clean:
	rm -f run-tests
	rm -rf run-tests.dSYM
