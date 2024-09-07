#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/local_socket"

int main() {
    int server_fd, client_fd;
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[256];

    // Создание сокета
    server_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        return 1;
    }

    // Удаление старого файла сокета, если существует
    unlink(SOCKET_PATH);

    // Установка параметров адреса
    server_addr.sun_family = AF_LOCAL;
    strcpy(server_addr.sun_path, SOCKET_PATH);

    // Привязка сокета к адресу
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        return 1;
    }

    // Ожидание подключений
    if (listen(server_fd, 5) < 0) {
        perror("listen");
        return 1;
    }

    printf("Server is waiting for connections...\n");

    // Прием клиента
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd < 0) {
        perror("accept");
        return 1;
    }

    // Чтение данных от клиента
    int bytes_read = read(client_fd, buffer, sizeof(buffer));
    if (bytes_read > 0) {
        printf("Received from client: %s\n", buffer);
        // Отправка ответа
        write(client_fd, "Hello from server!", 18);
    }

    // Закрытие соединений
    close(client_fd);
    close(server_fd);
    unlink(SOCKET_PATH); // Удаление файла сокета

    return 0;
}
