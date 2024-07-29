# Компилятор и флаги
CC = gcc
AR = ar
CFLAGS = -Wall -g

# Названия файлов и библиотек
LIBRARY = libcalc.a
LIB_SOURCES = add.c sub.c mul.c divv.c
LIB_OBJECTS = $(LIB_SOURCES:.c=.o)
PROGRAM = calculator
PROGRAM_SRC = main.c
PROGRAM_OBJ = main.o

# Главная цель - сборка всего проекта
all: $(PROGRAM)

# Правило для сборки библиотеки
$(LIBRARY): $(LIB_OBJECTS)
	$(AR) rcs $@ $(LIB_OBJECTS)

# Правило для сборки объектных файлов из исходников
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Правило для сборки основной программы
$(PROGRAM): $(PROGRAM_OBJ) $(LIBRARY)
	$(CC) $(CFLAGS) -o $@ $(PROGRAM_OBJ) -L. -lcalc

# Правило для сборки объектного файла основной программы
main.o: main.c calc.h
	$(CC) $(CFLAGS) -c main.c -o $@

# Очистка сгенерированных файлов
clean:
	rm -f $(PROGRAM) $(LIBRARY) $(LIB_OBJECTS) $(PROGRAM_OBJ)

# Файлы, которые не являются исходниками
.PHONY: all clean
