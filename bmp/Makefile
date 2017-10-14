CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lbmp -L.

build: libbmp.so test

bmp.o: bmp.cpp
	$(CC) $(CFLAGS) -fPIC -c $^ -o $@

libbmp.so: bmp.o
	$(CC) -shared $^ -o $@

test.o: main.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

test: test.o
	$(CC) -lstdc++ $(LDFLAGS) $^ -o $@

clean:
	rm libbmp.so bmp.o test.o test
