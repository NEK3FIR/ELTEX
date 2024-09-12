// multicast_sender.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MULTICAST_IP "224.0.0.1"  // Multicast группа
#define PORT 12345                // Порт для отправки сообщений
#define MESSAGE "hello"           // Сообщение для отправки
#define INTERVAL 1                // Интервал в секундах между отправкой сообщений

int main() {
    int sockfd;
    struct sockaddr_in multicast_addr;
    int ttl = 1;  // Time-to-live

    // Создаем UDP сокет
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Ошибка при создании сокета");
        exit(1);
    }

    // Устанавливаем TTL для multicast пакетов
    if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl)) < 0) {
        perror("Ошибка при установке TTL");
        exit(1);
    }

    // Заполняем адрес multicast группы
    memset(&multicast_addr, 0, sizeof(multicast_addr));
    multicast_addr.sin_family = AF_INET;
    multicast_addr.sin_addr.s_addr = inet_addr(MULTICAST_IP);
    multicast_addr.sin_port = htons(PORT);

    while (1) {
        // Отправляем сообщение в multicast группу
        if (sendto(sockfd, MESSAGE, strlen(MESSAGE), 0,
                   (struct sockaddr *)&multicast_addr, sizeof(multicast_addr)) < 0) {
            perror("Ошибка при отправке сообщения");
            exit(1);
        }

        printf("Сообщение '%s' отправлено\n", MESSAGE);
        sleep(INTERVAL);
    }

    close(sockfd);
    return 0;
}
