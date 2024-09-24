#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 8080
#define BUF_SIZE 1024
#define THREAD_POOL_SIZE 4
#define QUEUE_SIZE 16

pthread_t thread_pool[THREAD_POOL_SIZE];
int client_queue[QUEUE_SIZE];
int queue_size = 0;

pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t queue_cond = PTHREAD_COND_INITIALIZER;

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

void* thread_function(void* arg) {
    while (1) {
        pthread_mutex_lock(&queue_mutex);
        while (queue_size == 0) {
            pthread_cond_wait(&queue_cond, &queue_mutex);
        }
        int client_sock = client_queue[--queue_size];
        pthread_mutex_unlock(&queue_mutex);

        handle_client(&client_sock);
    }
}

int main() {
    for (int i = 0; i < THREAD_POOL_SIZE; ++i) {
        pthread_create(&thread_pool[i], NULL, thread_function, NULL);
    }

    int server_sock;
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

        pthread_mutex_lock(&queue_mutex);
        if (queue_size < QUEUE_SIZE) {
            client_queue[queue_size++] = client_sock;
            pthread_cond_signal(&queue_cond);
        } else {
            printf("Queue is full, rejecting client\n");
            close(client_sock);
        }
        pthread_mutex_unlock(&queue_mutex);
    }

    close(server_sock);
    return 0;
}
