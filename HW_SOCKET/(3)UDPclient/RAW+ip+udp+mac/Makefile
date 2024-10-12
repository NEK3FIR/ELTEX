CC = gcc
CFLAGS = -Wall -g
TARGET = raw_ethernet_udp_client

all: $(TARGET)

$(TARGET): raw_ethernet_udp_client.o
	$(CC) $(CFLAGS) -o $(TARGET) raw_ethernet_udp_client.o

raw_ethernet_udp_client.o: raw_ethernet_udp_client.c
	$(CC) $(CFLAGS) -c raw_ethernet_udp_client.c

clean:
	rm -f *.o $(TARGET)
