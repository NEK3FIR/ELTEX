# Название компилятора
CC = gcc

# Флаги компиляции
CFLAGS = -Wall -g

# Библиотеки для подключения
LIBS = -lpthread -lncurses

# Имена исходных файлов и целевых исполняемых файлов
SERVER_SRC = chat_server.c
CLIENT_SRC = chat_client.c
SERVER = chat_server
CLIENT = chat_client

# Правило по умолчанию: собирает оба исполняемых файла
all: $(SERVER) $(CLIENT)

# Правило для серверного исполняемого файла
$(SERVER): $(SERVER_SRC)
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_SRC) $(LIBS)

# Правило для клиентского исполняемого файла
$(CLIENT): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_SRC) $(LIBS)

# Очистка скомпилированных файлов
clean:
	rm -f $(SERVER) $(CLIENT)

# Полная пересборка (clean + all)
rebuild: clean all
