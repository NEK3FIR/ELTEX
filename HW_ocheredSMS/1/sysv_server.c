// sysv_server.c
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

    // Create message queue
    msgid = msgget(QUEUE_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("Server: msgget");
        exit(1);
    }

    // Send message
    message.msg_type = 1;
    strcpy(message.msg_text, "Hi!");
    if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1) {
        perror("Server: msgsnd");
        exit(1);
    }
    printf("Server: Sent message: %s\n", message.msg_text);

    // Receive response
    if (msgrcv(msgid, &message, sizeof(message.msg_text), 2, 0) == -1) {
        perror("Server: msgrcv");
        exit(1);
    }
    printf("Server: Received message: %s\n", message.msg_text);

    // Delete the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
