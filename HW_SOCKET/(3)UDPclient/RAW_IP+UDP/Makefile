CC = gcc
CFLAGS = -Wall -g
TARGET = raw_udp_client

all: $(TARGET)

$(TARGET): raw_udp_client.o
	$(CC) $(CFLAGS) -o $(TARGET) raw_udp_client.o

raw_udp_client.o: raw_udp_client.c
	$(CC) $(CFLAGS) -c raw_udp_client.c

clean:
	rm -f *.o $(TARGET)
