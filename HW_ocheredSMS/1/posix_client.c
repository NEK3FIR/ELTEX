#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <mqueue.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <unistd.h> 
 
#define SERVER_QUEUE_NAME   "/server_queue" 
#define MAX_MSG_SIZE 256 
#define MSG_BUFFER_SIZE (MAX_MSG_SIZE + 10) 
 
int main() { 
    mqd_t mq; 
    char buffer[MSG_BUFFER_SIZE]; 
 
    // Открываем очередь сообщений сервера 
    mq = mq_open(SERVER_QUEUE_NAME, O_RDWR); 
    if (mq == (mqd_t) -1) { 
        perror("Client: mq_open (server)"); 
        exit(1); 
    } 
 
    // Считываем сообщение от сервера 
    if (mq_receive(mq, buffer, MSG_BUFFER_SIZE, NULL) == -1) { 
        perror("Client: mq_receive"); 
        exit(1); 
    } 
    printf("Client: Received message from server: %s\n", buffer); 
 
    // Отправляем ответ серверу 
    sprintf(buffer, "Hello!"); 
    if (mq_send(mq, buffer, strlen(buffer) + 1, 0) == -1) { 
        perror("Client: Not able to send message to server"); 
        exit(1); 
    } 
    printf("Client: Sent message to server: %s\n", buffer); 
 
    // Закрываем очередь 
    if (mq_close(mq) == -1) { 
        perror("Client: mq_close"); 
        exit(1); 
    } 
 
    return 0; 
}
