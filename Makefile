CFLAGS= -g
LDFLAGS=
CC=g++

all: simulation

simulation: simulation.o Job.o AdmissionScheduler.o
	$(CC) $(LDFLAGS) -o simulation Job.o AdmissionScheduler.o simulation.o

.c.o:
	$(CC) $(CFLAGS) -c $*.c

clean:
	-rm simulation *.o
