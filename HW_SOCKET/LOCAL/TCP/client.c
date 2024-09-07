#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/local_socket"

int main() {
    int sock_fd;
    struct sockaddr_un server_addr;
    char buffer[256] = "Hello from client!";

    // Создание сокета
    sock_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("socket");
        return 1;
    }

    // Установка параметров адреса сервера
    server_addr.sun_family = AF_LOCAL;
    strcpy(server_addr.sun_path, SOCKET_PATH);

    // Подключение к серверу
    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        return 1;
    }

    // Отправка сообщения серверу
    write(sock_fd, buffer, sizeof(buffer));

    // Чтение ответа от сервера
    int bytes_read = read(sock_fd, buffer, sizeof(buffer));
    if (bytes_read > 0) {
        printf("Received from server: %s\n", buffer);
    }

    // Закрытие сокета
    close(sock_fd);

    return 0;
}
