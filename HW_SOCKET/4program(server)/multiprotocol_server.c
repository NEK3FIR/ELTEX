#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/select.h>

#define TCP_PORT 8080
#define UDP_PORT 8081
#define BUF_SIZE 1024

int main() {
    int tcp_sock, udp_sock;
    struct sockaddr_in tcp_addr, udp_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUF_SIZE];
    fd_set readfds;

    // Создание TCP сокета
    tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_sock == -1) {
        perror("TCP socket failed");
        exit(EXIT_FAILURE);
    }
    tcp_addr.sin_family = AF_INET;
    tcp_addr.sin_addr.s_addr = INADDR_ANY;
    tcp_addr.sin_port = htons(TCP_PORT);
    if (bind(tcp_sock, (struct sockaddr*)&tcp_addr, sizeof(tcp_addr)) < 0) {
        perror("TCP bind failed");
        exit(EXIT_FAILURE);
    }
    listen(tcp_sock, 10);

    // Создание UDP сокета
    udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_sock == -1) {
        perror("UDP socket failed");
        exit(EXIT_FAILURE);
    }
    udp_addr.sin_family = AF_INET;
    udp_addr.sin_addr.s_addr = INADDR_ANY;
    udp_addr.sin_port = htons(UDP_PORT);
    if (bind(udp_sock, (struct sockaddr*)&udp_addr, sizeof(udp_addr)) < 0) {
        perror("UDP bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on TCP port %d and UDP port %d\n", TCP_PORT, UDP_PORT);

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(tcp_sock, &readfds);
        FD_SET(udp_sock, &readfds);
        int max_sd = (tcp_sock > udp_sock) ? tcp_sock : udp_sock;

        if (select(max_sd + 1, &readfds, NULL, NULL, NULL) < 0) {
            perror("Select error");
            exit(EXIT_FAILURE);
        }

        // Обработка TCP клиента
        if (FD_ISSET(tcp_sock, &readfds)) {
            int client_sock = accept(tcp_sock, (struct sockaddr*)&client_addr, &addr_len);
            if (client_sock < 0) {
                perror("TCP accept failed");
                exit(EXIT_FAILURE);
            }
            int bytes_read = recv(client_sock, buffer, BUF_SIZE, 0);
            send(client_sock, buffer, bytes_read, 0);
            close(client_sock);
        }

        // Обработка UDP клиента
        if (FD_ISSET(udp_sock, &readfds)) {
            int bytes_read = recvfrom(udp_sock, buffer, BUF_SIZE, 0, (struct sockaddr*)&client_addr, &addr_len);
            sendto(udp_sock, buffer, bytes_read, 0, (struct sockaddr*)&client_addr, addr_len);
        }
    }

    close(tcp_sock);
    close(udp_sock);
    return 0;
}
