CFLAGS= -g
LDFLAGS=
CC=g++

all: simulation

simulation: simulation.o Job.o Stats.o AdmissionScheduler.o CPUScheduler.o
	$(CC) $(LDFLAGS) -o simulation Job.o Stats.o AdmissionScheduler.o CPUScheduler.o simulation.o

.c.o:
	$(CC) $(CFLAGS) -c $*.cpp

clean:
	-rm simulation *.o
