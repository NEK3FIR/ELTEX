// broadcast_sender.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BROADCAST_IP "255.255.255.255"  // Broadcast адрес
#define PORT 12345                      // Порт для отправки сообщений
#define MESSAGE "hello"                 // Сообщение для отправки
#define INTERVAL 1                      // Интервал в секундах между отправками

int main() {
    int sockfd;
    struct sockaddr_in broadcast_addr;
    int broadcast_enable = 1;

    // Создаем UDP сокет
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Ошибка при создании сокета");
        exit(1);
    }

    // Включаем режим broadcast для сокета
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast_enable, sizeof(broadcast_enable)) < 0) {
        perror("Ошибка при включении broadcast");
        exit(1);
    }

    // Заполняем адрес broadcast
    memset(&broadcast_addr, 0, sizeof(broadcast_addr));
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_addr.s_addr = inet_addr(BROADCAST_IP);
    broadcast_addr.sin_port = htons(PORT);

    while (1) {
        // Отправляем сообщение через broadcast
        if (sendto(sockfd, MESSAGE, strlen(MESSAGE), 0, (struct sockaddr *)&broadcast_addr, sizeof(broadcast_addr)) < 0) {
            perror("Ошибка при отправке broadcast сообщения");
            exit(1);
        }

        printf("Сообщение '%s' отправлено\n", MESSAGE);
        sleep(INTERVAL);
    }

    close(sockfd);
    return 0;
}
