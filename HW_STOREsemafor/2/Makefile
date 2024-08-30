CC = gcc
CFLAGS = -Wall -pthread
TARGETS = server client

all: $(TARGETS)

server: server.c
	$(CC) $(CFLAGS) -o server server.c

client: client.c
	$(CC) $(CFLAGS) -o client client.c -lncurses

clean:
	rm -f $(TARGETS)