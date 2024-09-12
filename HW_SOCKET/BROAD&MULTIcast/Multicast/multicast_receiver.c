// multicast_receiver.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MULTICAST_IP "224.0.0.1"  // Multicast группа
#define PORT 12345                // Порт для получения сообщений
#define BUFFER_SIZE 1024          // Размер буфера для сообщений

int main() {
    int sockfd;
    struct sockaddr_in local_addr;
    struct ip_mreq multicast_req;
    char buffer[BUFFER_SIZE];

    // Создаем UDP сокет
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Ошибка при создании сокета");
        exit(1);
    }

    // Привязываем сокет к локальному адресу и порту
    memset(&local_addr, 0, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    local_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&local_addr, sizeof(local_addr)) < 0) {
        perror("Ошибка при привязке сокета");
        exit(1);
    }

    // Присоединяемся к multicast группе
    multicast_req.imr_multiaddr.s_addr = inet_addr(MULTICAST_IP);
    multicast_req.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &multicast_req, sizeof(multicast_req)) < 0) {
        perror("Ошибка при присоединении к multicast группе");
        exit(1);
    }

    // Принимаем сообщения
    while (1) {
        int nbytes = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0, NULL, NULL);
        if (nbytes < 0) {
            perror("Ошибка при получении данных");
            exit(1);
        }

        buffer[nbytes] = '\0';  // Завершаем строку
        printf("Получено сообщение: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}
