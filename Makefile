CFLAGS=-O0 -ggdb3 -g3 -Wall -Wextra
LINKFLAGS=-lm -lncurses

all: main

math: src/renderMath.c src/include/renderMath.h
	$(CC) $(CFLAGS) -c -o renderMath.o src/renderMath.c $(LINKFLAGS)

render: math src/renderFrontend.c src/include/renderFrontend.h
	$(CC) $(CFLAGS) -c -o renderFrontend.o src/renderFrontend.c $(LINKFLAGS)

test: math src/test.c
	$(CC) $(CFLAGS) -o test.out renderMath.o src/test.c $(LINKFLAGS)

main: render math src/main.c
	$(CC) $(CFLAGS) -o main.out renderMath.o renderFrontend.o src/main.c $(LINKFLAGS)
