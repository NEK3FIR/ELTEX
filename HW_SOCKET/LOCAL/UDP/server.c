#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/local_udp_socket"
#define BUFFER_SIZE 1024

int main() {
    int server_fd;
    struct sockaddr_un server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t client_len = sizeof(client_addr);

    // Создание сокета
    server_fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if (server_fd < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Удаление старого файла сокета, если он существует
    unlink(SOCKET_PATH);

    // Установка параметров адреса
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_LOCAL;
    strcpy(server_addr.sun_path, SOCKET_PATH);

    // Привязка сокета к адресу
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is waiting for messages...\n");

    // Получение сообщения от клиента
    int recv_len = recvfrom(server_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &client_len);
    if (recv_len > 0) {
        buffer[recv_len] = '\0';
        printf("Received from client: %s\n", buffer);

        // Отправка ответа клиенту
        const char *response = "Hello from server!";
        sendto(server_fd, response, strlen(response), 0, (struct sockaddr *)&client_addr, client_len);
    }

    // Закрытие сокета
    close(server_fd);
    unlink(SOCKET_PATH);  // Удаление файла сокета

    return 0;
}
