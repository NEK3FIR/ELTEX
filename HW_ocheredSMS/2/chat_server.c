#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_TEXT 512

struct msg_buffer {
    long msg_type;
    char msg_text[MAX_TEXT];
};

int msgid;

void* receive_messages(void* arg) {
    struct msg_buffer message;
    while(1) {
        msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);
        printf("New message: %s\n", message.msg_text);
    }
    return NULL;
}

int main() {
    key_t key;
    struct msg_buffer message;

    // Generate unique key
    key = ftok("chat", 65);

    // Create message queue and return id
    msgid = msgget(key, 0666 | IPC_CREAT);

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, receive_messages, NULL);

    while (1) {
        fgets(message.msg_text, MAX_TEXT, stdin);
        message.msg_type = 1;
        msgsnd(msgid, &message, sizeof(message.msg_text), 0);
    }

    pthread_join(thread_id, NULL);
    msgctl(msgid, IPC_RMID, NULL);  // Destroy the message queue

    return 0;
}
