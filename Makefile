CC=gcc
CFLAGS=-g -Wall
SRC=src/main.c

main: $(SRC)
	$(CC) $(CFLAGS) -o dummygen $(SRC)
