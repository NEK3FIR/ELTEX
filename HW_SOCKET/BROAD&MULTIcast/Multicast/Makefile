CC = gcc
CFLAGS = -Wall -g
TARGETS = multicast_sender multicast_receiver

all: $(TARGETS)

multicast_sender: multicast_sender.c
	$(CC) $(CFLAGS) -o multicast_sender multicast_sender.c

multicast_receiver: multicast_receiver.c
	$(CC) $(CFLAGS) -o multicast_receiver multicast_receiver.c

clean:
	rm -f $(TARGETS)
