#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int client_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    const char *message = "Hello from client!";

    // Создание сокета
    if ((client_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Установка параметров адреса сервера
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    
    // Преобразование IP-адреса сервера в бинарный формат
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    // Отправка сообщения серверу
    sendto(client_fd, message, strlen(message), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Message sent to server\n");

    // Получение ответа от сервера
    socklen_t server_addr_len = sizeof(server_addr);
    int recv_len = recvfrom(client_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &server_addr_len);
    if (recv_len > 0) {
        buffer[recv_len] = '\0';
        printf("Received from server: %s\n", buffer);
    }

    // Закрытие сокета
    close(client_fd);
    return 0;
}

