CC = gcc
CFLAGS = -Wall -g
TARGETS = broadcast_sender broadcast_receiver

all: $(TARGETS)

broadcast_sender: broadcast_sender.c
	$(CC) $(CFLAGS) -o broadcast_sender broadcast_sender.c

broadcast_receiver: broadcast_receiver.c
	$(CC) $(CFLAGS) -o broadcast_receiver broadcast_receiver.c

clean:
	rm -f $(TARGETS)
