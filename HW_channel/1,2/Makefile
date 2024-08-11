CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJ = pipe_example.o server.o client.o

all: pipe_example server client

pipe_example: pipe_example.c
	$(CC) $(CFLAGS) -o $@ $^

server: server.c
	$(CC) $(CFLAGS) -o $@ $^

client: client.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f pipe_example server client
