#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <unistd.h>

// Функция для вычисления контрольной суммы
unsigned short checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum = 0;
    unsigned short result;

    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;
    if (len == 1)
        sum += *(unsigned char *)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

int main() {
    // Создаем RAW-сокет
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (sock < 0) {
        perror("Ошибка создания сокета");
        return 1;
    }

    // Буфер для пакета
    char packet[4096];
    memset(packet, 0, sizeof(packet));

    // Указатели на заголовки IP и UDP
    struct iphdr *iph = (struct iphdr *)packet;
    struct udphdr *udph = (struct udphdr *)(packet + sizeof(struct iphdr));

    // Данные для UDP
    char *data = packet + sizeof(struct iphdr) + sizeof(struct udphdr);
    const char *message = "Привет от RAW UDP клиента";
    int data_len = strlen(message);
    strcpy(data, message);

    // Настраиваем адрес назначения
    struct sockaddr_in dest;
    dest.sin_family = AF_INET;
    dest.sin_port = htons(8080);  // Порт назначения
    dest.sin_addr.s_addr = inet_addr("192.168.1.2");  // IP назначения

    // Заполняем IP-заголовок
    iph->ihl = 5;  // Длина заголовка
    iph->version = 4;  // Версия IP (IPv4)
    iph->tos = 0;  // Тип обслуживания
    iph->tot_len = htons(sizeof(struct iphdr) + sizeof(struct udphdr) + data_len);  // Общая длина пакета
    iph->id = htonl(54321);  // Идентификатор пакета
    iph->frag_off = 0;  // Флаги фрагментации
    iph->ttl = 64;  // Время жизни пакета
    iph->protocol = IPPROTO_UDP;  // Протокол (UDP)
    iph->saddr = inet_addr("192.168.1.1");  // IP-адрес отправителя
    iph->daddr = dest.sin_addr.s_addr;  // IP-адрес назначения

    // Вычисляем контрольную сумму IP
    iph->check = checksum((unsigned short *)iph, sizeof(struct iphdr));

    // Заполняем UDP-заголовок
    udph->source = htons(12345);  // Порт отправителя
    udph->dest = htons(8080);  // Порт назначения
    udph->len = htons(sizeof(struct udphdr) + data_len);  // Длина UDP
    udph->check = 0;  // Контрольная сумма может быть 0 для UDP

    // Отправляем пакет
    if (sendto(sock, packet, sizeof(struct iphdr) + sizeof(struct udphdr) + data_len, 0, (struct sockaddr *)&dest, sizeof(dest)) < 0) {
        perror("Ошибка отправки");
        close(sock);
        return 1;
    }

    printf("Пакет отправлен!\n");

    // Закрываем сокет
    close(sock);
    return 0;
}
