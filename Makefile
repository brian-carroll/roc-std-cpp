CC = clang++
CFLAGS = -g -Wall -std=c++11
HEADERS = $(wildcard src/*.h) $(wildcard test/lib/*.h)

all: run-tests

run-tests: test/main.cpp $(HEADERS)
	$(CC) $(CFLAGS) -Isrc -Itest/lib -o $@ $<

check: run-tests
	./run-tests

clean:
	rm -f run-tests
	rm -rf run-tests.dSYM
