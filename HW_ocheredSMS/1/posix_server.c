#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <mqueue.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <unistd.h> 
 
#define SERVER_QUEUE_NAME   "/server_queue" 
#define QUEUE_PERMISSIONS 0660 
#define MAX_MSG_SIZE 256 
#define MSG_BUFFER_SIZE (MAX_MSG_SIZE + 10) 
 
int main() { 
    mqd_t mq; 
    struct mq_attr attr; 
    char buffer[MSG_BUFFER_SIZE]; 
 
    // Настройка атрибутов очереди 
    attr.mq_flags = 0; 
    attr.mq_maxmsg = 10; 
    attr.mq_msgsize = MAX_MSG_SIZE; 
    attr.mq_curmsgs = 0; 
 
    // Создаем очередь сообщений 
    mq = mq_open(SERVER_QUEUE_NAME, O_CREAT | O_RDWR, QUEUE_PERMISSIONS, &attr); 
    if (mq == (mqd_t) -1) { 
        perror("Server: mq_open (server)"); 
        exit(1); 
    } 
 
    // Отправляем сообщение клиенту 
    sprintf(buffer, "Hi!"); 
    if (mq_send(mq, buffer, strlen(buffer) + 1, 0) == -1) { 
        perror("Server: Not able to send message to client"); 
        exit(1); 
    } 
    printf("Server: Sent message to client: %s\n", buffer); 
 
    // Ждем ответа от клиента 
    if (mq_receive(mq, buffer, MSG_BUFFER_SIZE, NULL) == -1) { 
        perror("Server: mq_receive"); 
        exit(1); 
    } 
    printf("Server: Received message from client: %s\n", buffer); 
 
    // Закрываем и удаляем очередь 
    if (mq_close(mq) == -1) { 
        perror("Server: mq_close"); 
        exit(1); 
    } 
 
    if (mq_unlink(SERVER_QUEUE_NAME) == -1) { 
        perror("Server: mq_unlink"); 
        exit(1); 
    } 
 
    return 0; 
}
