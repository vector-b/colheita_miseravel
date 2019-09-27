# Makefile
LDFLAGS=-lncurses

all: jogo

jogo: main.o jogo.o
	gcc  main.o jogo.o -o jogo -Wall -lncurses

main.o: main.c jogo.h
	gcc -c main.c -Wall -lncurses

jogo.o: jogo.c jogo.h
	gcc -c jogo.c -Wall -lncurses

clean:
	rm -rf *.o
