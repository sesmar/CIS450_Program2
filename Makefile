CFLAGS= -g
LDFLAGS=
CC=g++

all: simulation

simulation: simulation.o
	$(CC) $(LDFLAGS) -o simulation simulation.o

.c.o:
	$(CC) $(CFLAGS) -c $*.c

clean:
	-rm simulation *.o
