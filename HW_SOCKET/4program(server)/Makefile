CC = gcc
CFLAGS = -Wall -pthread

all: parallel_server thread_pool_server queue_server multiprotocol_server

parallel_server: parallel_server.c
	$(CC) $(CFLAGS) -o parallel_server parallel_server.c

thread_pool_server: thread_pool_server.c
	$(CC) $(CFLAGS) -o thread_pool_server thread_pool_server.c

queue_server: queue_server.c
	$(CC) $(CFLAGS) -o queue_server queue_server.c

multiprotocol_server: multiprotocol_server.c
	$(CC) $(CFLAGS) -o multiprotocol_server multiprotocol_server.c

clean:
	rm -f parallel_server thread_pool_server queue_server multiprotocol_server
