CC = gcc
CFLAGS = -g -Wall -std=c11

all: P11 P12 P2

P2: P2.c
	$(CC) $(CFLAGS) -o P2 P2.c
P11: P11.c
	$(CC) $(CFLAGS) -o P11 P11.c -lm
P12: P12.c
	$(CC) $(CFLAGS) -o P12 P12.c -lm
clean:
	rm -f P2 P11 P12