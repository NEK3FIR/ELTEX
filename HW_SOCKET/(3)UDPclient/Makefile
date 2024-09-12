# Указываем компилятор
CC = gcc

# Флаги компиляции
CFLAGS = -Wall -g

# Названия исполняемых файлов
SERVER_EXEC = udp_server
CLIENT_EXEC = udp_client_raw

# Названия исходных файлов
SERVER_SRC = server.c
CLIENT_SRC = udp_client_raw.c

# Цель по умолчанию - компилировать оба файла
all: $(SERVER_EXEC) $(CLIENT_EXEC)

# Компиляция сервера
$(SERVER_EXEC): $(SERVER_SRC)
	$(CC) $(CFLAGS) -o $(SERVER_EXEC) $(SERVER_SRC)

# Компиляция клиента
$(CLIENT_EXEC): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -o $(CLIENT_EXEC) $(CLIENT_SRC)

# Удаление скомпилированных файлов
clean:
	rm -f $(SERVER_EXEC) $(CLIENT_EXEC)

# Ручная переустановка (очистка и компиляция заново)
rebuild: clean all
