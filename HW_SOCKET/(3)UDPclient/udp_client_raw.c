#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <sys/socket.h>

#define DEST_PORT 8080     // Порт сервера
#define SOURCE_PORT 12345  // Произвольный исходящий порт
#define DEST_IP "127.0.0.1" // IP-адрес сервера
#define BUFFER_SIZE 1024

// Структура UDP заголовка
struct udpheader {
    unsigned short source_port;
    unsigned short dest_port;
    unsigned short length;
    unsigned short checksum;
};

// Функция для вычисления контрольной суммы (здесь 0 для простоты)
unsigned short checksum(void *b, int len) {
    return 0; // Контрольная сумма всегда равна 0 в этой задаче
}

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];

    // Создание сырого сокета для отправки UDP пакетов
    if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Заполнение адреса сервера
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(DEST_PORT);
    serv_addr.sin_addr.s_addr = inet_addr(DEST_IP);

    // Заполнение UDP заголовка
    struct udpheader udp;
    udp.source_port = htons(SOURCE_PORT);        // Исходный порт
    udp.dest_port = htons(DEST_PORT);            // Порт назначения
    udp.length = htons(sizeof(struct udpheader) + strlen("hello!"));  // Длина UDP сегмента
    udp.checksum = 0;                            // Контрольная сумма = 0

    // Копируем UDP заголовок и данные в буфер
    memset(buffer, 0, BUFFER_SIZE);
    memcpy(buffer, &udp, sizeof(struct udpheader));  // Копируем UDP заголовок
    strcpy(buffer + sizeof(struct udpheader), "hello!"); // Добавляем данные ("hello!")

    // Отправка пакета серверу
    if (sendto(sockfd, buffer, sizeof(struct udpheader) + strlen("hello!"), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("sendto failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("Packet sent to server\n");

    // Ожидание ответа от сервера
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL);
        if (len > 0) {
            printf("Received from server: %s\n", buffer + sizeof(struct iphdr) + sizeof(struct udpheader)); // Пропускаем IP и UDP заголовки
            break;
        }
    }

    // Закрытие сокета
    close(sockfd);
    return 0;
}
