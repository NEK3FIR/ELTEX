#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/ether.h>
#include <netpacket/packet.h>
#include <net/if.h>
#include <sys/ioctl.h>

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
    // Создаем RAW-сокет для отправки Ethernet кадров
    int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sock < 0) {
        perror("Ошибка создания сокета");
        return 1;
    }

    // Буфер для пакета
    char packet[65536];
    memset(packet, 0, sizeof(packet));

    // Указатели на заголовки Ethernet, IP и UDP
    struct ether_header *eth = (struct ether_header *)packet;
    struct iphdr *iph = (struct iphdr *)(packet + sizeof(struct ether_header));
    struct udphdr *udph = (struct udphdr *)(packet + sizeof(struct ether_header) + sizeof(struct iphdr));

    // Данные для UDP
    char *data = packet + sizeof(struct ether_header) + sizeof(struct iphdr) + sizeof(struct udphdr);
    const char *message = "Привет от RAW Ethernet UDP клиента";
    int data_len = strlen(message);
    strcpy(data, message);

    // Заполняем Ethernet-заголовок
    eth->ether_shost[0] = 0x00;  // MAC-адрес отправителя
    eth->ether_shost[1] = 0x0c;
    eth->ether_shost[2] = 0x29;
    eth->ether_shost[3] = 0x3e;
    eth->ether_shost[4] = 0x44;
    eth->ether_shost[5] = 0x2b;

    eth->ether_dhost[0] = 0x00;  // MAC-адрес получателя
    eth->ether_dhost[1] = 0x0c;
    eth->ether_dhost[2] = 0x29;
    eth->ether_dhost[3] = 0x3e;
    eth->ether_dhost[4] = 0x44;
    eth->ether_dhost[5] = 0x2c;

    eth->ether_type = htons(ETH_P_IP);  // Тип протокола (IP)

    // Заполняем IP-заголовок
    iph->ihl = 5;  // Длина заголовка
    iph->version = 4;  // Версия IP
    iph->tos = 0;
    iph->tot_len = htons(sizeof(struct iphdr) + sizeof(struct udphdr) + data_len);
    iph->id = htonl(54321);  // Идентификатор пакета
    iph->frag_off = 0;
    iph->ttl = 64;
    iph->protocol = IPPROTO_UDP;
    iph->saddr = inet_addr("192.168.1.1");
    iph->daddr = inet_addr("192.168.1.2");

    // Вычисляем контрольную сумму IP-заголовка
    iph->check = checksum((unsigned short *)iph, sizeof(struct iphdr));

    // Заполняем UDP-заголовок
    udph->source = htons(12345);
    udph->dest = htons(8080);
    udph->len = htons(sizeof(struct udphdr) + data_len);
    udph->check = 0;  // Контрольная сумма 0 для UDP

    // Настройка интерфейса для отправки
    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, "eth0", IFNAMSIZ - 1);

    if (ioctl(sock, SIOCGIFINDEX, &ifr) < 0) {
        perror("Ошибка получения индекса интерфейса");
        close(sock);
        return 1;
    }

    struct sockaddr_ll sa;
    memset(&sa, 0, sizeof(sa));
    sa.sll_ifindex = ifr.ifr_ifindex;
    sa.sll_halen = ETH_ALEN;
    memcpy(sa.sll_addr, eth->ether_dhost, ETH_ALEN);

    // Отправляем пакет
    if (sendto(sock, packet, sizeof(struct ether_header) + sizeof(struct iphdr) + sizeof(struct udphdr) + data_len, 0, (struct sockaddr *)&sa, sizeof(sa)) < 0) {
        perror("Ошибка отправки");
        close(sock);
        return 1;
    }

    printf("Ethernet пакет отправлен!\n");

    close(sock);
    return 0;
}

