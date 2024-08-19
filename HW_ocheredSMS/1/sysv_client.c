// sysv_client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define QUEUE_KEY 1234

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    int msgid;
    struct msg_buffer message;

    // Get message queue
    msgid = msgget(QUEUE_KEY, 0666);
    if (msgid == -1) {
        perror("Client: msgget");
        exit(1);
    }

    // Receive message
    if (msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0) == -1) {
        perror("Client: msgrcv");
        exit(1);
    }
    printf("Client: Received message: %s\n", message.msg_text);

    // Send response
    message.msg_type = 2;
    strcpy(message.msg_text, "Hello!");
    if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1) {
        perror("Client: msgsnd");
        exit(1);
    }
    printf("Client: Sent message: %s\n", message.msg_text);

    return 0;
}
