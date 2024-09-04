CC = gcc
CFLAGS = -Wall -g

all: receiver sender

receiver: receiver.c
	$(CC) $(CFLAGS) -o receiver receiver.c

sender: sender.c
	$(CC) $(CFLAGS) -o sender sender.c

clean:
	rm -f receiver sender
