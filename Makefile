CC=gcc
CFLAGS=-g
SRC=src/main.c

main: $(SRC)
	$(CC) $(CFLAGS) -o dummygen $(SRC)
