# Makefile

CC = gcc
CFLAGS = -Wall

all: server_posix client_posix server_sysv client_sysv

server_posix: server_posix.c
	$(CC) $(CFLAGS) -o server_posix server_posix.c -lrt

client_posix: client_posix.c
	$(CC) $(CFLAGS) -o client_posix client_posix.c -lrt

server_sysv: server_sysv.c
	$(CC) $(CFLAGS) -o server_sysv server_sysv.c

client_sysv: client_sysv.c
	$(CC) $(CFLAGS) -o client_sysv client_sysv.c

clean:
	rm -f server_posix client_posix server_sysv client_sysv
