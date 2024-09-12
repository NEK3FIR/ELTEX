#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/local_udp_socket"
#define BUFFER_SIZE 1024

int main() {
    int client_fd;
    struct sockaddr_un server_addr;
    char buffer[BUFFER_SIZE];
    const char *message = "Hello from client!";

    // Создание сокета
    client_fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if (client_fd < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Установка параметров адреса сервера
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_LOCAL;
    strcpy(server_addr.sun_path, SOCKET_PATH);

    // Отправка сообщения серверу
    sendto(client_fd, message, strlen(message), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Message sent to server\n");

    // Получение ответа от сервера
    int recv_len = recvfrom(client_fd, buffer, BUFFER_SIZE, 0, NULL, NULL);
    if (recv_len > 0) {
        buffer[recv_len] = '\0';
        printf("Received from server: %s\n", buffer);
    }

    // Закрытие сокета
    close(client_fd);

    return 0;
}
