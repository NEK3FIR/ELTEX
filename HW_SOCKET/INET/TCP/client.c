#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE] = {0};
    char *message = "Hello from client!";

    // Создание сокета
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    // Установка параметров адреса сервера
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // Преобразование IP-адреса в бинарный формат
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    // Подключение к серверу
    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection Failed");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    // Отправка сообщения серверу
    send(sock_fd, message, strlen(message), 0);
    printf("Message sent to server\n");

    // Чтение ответа от сервера
    int valread = read(sock_fd, buffer, BUFFER_SIZE);
    printf("Received from server: %s\n", buffer);

    // Закрытие сокета
    close(sock_fd);

    return 0;
}
