# Makefile

CC = gcc
CFLAGS = -fPIC -Wall -Wextra
LDFLAGS = -shared
DLFLAGS = -ldl

LIB_NAME = libcalc.so
TARGET = main

SRC = add.c sub.c mul.c divv.c
OBJ = $(SRC:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(LIB_NAME): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): main.c $(LIB_NAME)
	$(CC) -o $@ main.c $(DLFLAGS)

clean:
	rm -f $(OBJ) $(LIB_NAME) $(TARGET)
