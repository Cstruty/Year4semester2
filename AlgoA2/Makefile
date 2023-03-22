CC = gcc
CFLAGS = -g -Wall -std=c11
MATH =-lm

all: P11 P12 P21 P22

P11: P11.c
	$(CC) $(CFLAGS) -o P11 P11.c $(MATH)

P12: P12.c
	$(CC) $(CFLAGS) -o P12 P12.c $(MATH)

P21: P21.c
	$(CC) $(CFLAGS) -o P21 P21.c $(MATH)

P22: P22.c
	$(CC) $(CFLAGS) -o P22 P22.c $(MATH)

clean:
	rm -f P11 P12 P21 P22
