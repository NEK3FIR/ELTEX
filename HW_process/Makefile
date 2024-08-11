CC = gcc
CFLAGS = -Wall -g
TARGETS = main1 main2 main3

all: $(TARGETS)

main1: main1.c
	$(CC) $(CFLAGS) -o main1 main1.c

main2: main2.c
	$(CC) $(CFLAGS) -o main2 main2.c

main3: main3.c
	$(CC) $(CFLAGS) -o main3 main3.c

clean:
	rm -f $(TARGETS) *.o

.PHONY: all clean
