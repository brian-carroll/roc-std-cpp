CC = clang++
CFLAGS = -g -Wall

all: test/run

test/run: test/main.cpp
	$(CC) $(CFLAGS) -Isrc -o $@ $<

check: test/run
	test/run

clean:
	rm -f test/run **/*.o
