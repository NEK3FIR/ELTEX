# Указание компилятора
CC = gcc

# Флаги компилятора
CFLAGS = -Wall -g

# Имя исполняемого файла
TARGET = eventloop

# Правило для сборки исполняемого файла
all: $(TARGET)

# Правило для сборки blocker
$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

# Правило для очистки скомпилированных файлов
clean:
	rm -f $(TARGET)

# Дополнительное правило для запуска программы
run: $(TARGET)
	./$(TARGET)

# Правило для повторной сборки
rebuild: clean all
