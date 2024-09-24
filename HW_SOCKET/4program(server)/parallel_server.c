#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

void* handle_client(void* arg) {
    int client_sock = *((int*)arg);
    free(arg);

    char buffer[BUF_SIZE];
    int bytes_read;
    while ((bytes_read = recv(client_sock, buffer, BUF_SIZE, 0)) > 0) {
        send(client_sock, buffer, bytes_read, 0);  // Эхо-сервер
    }

    close(client_sock);
    return NULL;
}

int main() {
    int server_sock, *new_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    listen(server_sock, 10);
    printf("Server listening on port %d\n", PORT);

    while (1) {
        int client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_len);
        if (client_sock < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        pthread_t client_thread;
        new_sock = malloc(sizeof(int));
        *new_sock = client_sock;
        pthread_create(&client_thread, NULL, handle_client, (void*)new_sock);
        pthread_detach(client_thread);
    }

    close(server_sock);
    return 0;
}
