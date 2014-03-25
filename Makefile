CFLAGS= -g
LDFLAGS=
CC=g++

all: simulation

simulation: simulation.o Job.o
	$(CC) $(LDFLAGS) -o simulation Job.o simulation.o

.c.o:
	$(CC) $(CFLAGS) -c $*.c

clean:
	-rm simulation *.o
