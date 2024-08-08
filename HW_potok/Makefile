# file: Makefile
CC = gcc
CFLAGS = -Wall -pthread
TARGETS = thread_index mutex_increment simulation

all: $(TARGETS)

thread_index: thread_index.c
	$(CC) $(CFLAGS) -o thread_index thread_index.c

mutex_increment: mutex_increment.c
	$(CC) $(CFLAGS) -o mutex_increment mutex_increment.c

simulation: simulation.c
	$(CC) $(CFLAGS) -o simulation simulation.c

clean:
	rm -f $(TARGETS)
