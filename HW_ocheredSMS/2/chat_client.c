#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <ncurses.h>
#include <unistd.h>

#define MAX_TEXT 512

struct msg_buffer {
    long msg_type;
    char msg_text[MAX_TEXT];
};

int msgid;
WINDOW *chatwin, *inputwin;

void* receive_messages(void* arg) {
    struct msg_buffer message;
    while(1) {
        msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);
        wprintw(chatwin, "%s", message.msg_text);
        wrefresh(chatwin);
    }
    return NULL;
}

int main() {
    key_t key;
    struct msg_buffer message;
    char name[50];

    // Initialize ncurses
    initscr();
    cbreak();
    noecho();

    int height = 20, width = 50;
    int starty = 0, startx = 0;

    chatwin = newwin(height, width, starty, startx);
    inputwin = newwin(3, width, height, startx);
    scrollok(chatwin, TRUE);
    scrollok(inputwin, TRUE);

    // Generate unique key
    key = ftok("chat", 65);

    // Connect to the message queue
    msgid = msgget(key, 0666 | IPC_CREAT);

    wprintw(inputwin, "Enter your name: ");
    wrefresh(inputwin);
    wgetstr(inputwin, name);

    // Notify server of new participant
    sprintf(message.msg_text, "%s has joined the chat\n", name);
    message.msg_type = 1;
    msgsnd(msgid, &message, sizeof(message.msg_text), 0);

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, receive_messages, NULL);

    while(1) {
        wclear(inputwin);
        wprintw(inputwin, "You: ");
        wrefresh(inputwin);
        wgetstr(inputwin, message.msg_text);
        sprintf(message.msg_text, "%s: %s\n", name, message.msg_text);
        message.msg_type = 1;
        msgsnd(msgid, &message, sizeof(message.msg_text), 0);
    }

    pthread_join(thread_id, NULL);
    endwin();
    
    return 0;
}
