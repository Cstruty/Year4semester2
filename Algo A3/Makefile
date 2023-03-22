CC = gcc
CFLAGS = -g -Wall -std=c11

all: P21 P22 P23 P11 P12

P21: P21.c
	$(CC) $(CFLAGS) -o P21 P21.c


P22: P22.c
	$(CC) $(CFLAGS) -o P22 P22.c
P23: P23.c
	$(CC) $(CFLAGS) -o P23 P23.c -lm
P11: P11.c
	$(CC) $(CFLAGS) -o P11 P11.c -lm
P12: P12.c
	$(CC) $(CFLAGS) -o P12 P12.c -lm
clean:
	rm -f P21 P22 P23 P11 P12