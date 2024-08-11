CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = mybash

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	rm -f $(TARGET)
