# Имя исполняемого файла
TARGET = file

# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Исходные файлы
SRC = file.c

# Правило по умолчанию
all: $(TARGET)

# Правило сборки исполняемого файла
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Правило для очистки
clean:
	rm -f $(TARGET)

# Файлы, не являющиеся целями
.PHONY: all clean
