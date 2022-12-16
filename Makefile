CFLAGS=-O0 -ggdb3 -g3 -Wall -Wextra
LINKFLAGS=-lm -lncurses

math: src/renderMath.c src/include/renderMath.h
	$(CC) $(CFLAGS) -c -o renderMath.o src/renderMath.c $(LINKFLAGS)

test: math src/test.c
	$(CC) $(CFLAGS) -o test.out src/test.c
