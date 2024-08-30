#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>
#include <ncurses.h>
#include <sys/stat.h>

#define SHM_NAME "/chat_shm"
#define SHM_SIZE 4096
#define MSG_SIZE 256

typedef struct {
    int num_clients;
    char messages[SHM_SIZE - sizeof(int)];
} ChatRoom;

WINDOW *chat_win, *input_win, *users_win;

void *receive_messages(void *arg) {
    ChatRoom *chat = (ChatRoom *)arg;
    int prev_num_clients = 0;

    while (1) {
        if (chat->num_clients != prev_num_clients) {
            werase(users_win);
            mvwprintw(users_win, 1, 1, "Users: %d", chat->num_clients);
            wrefresh(users_win);
            prev_num_clients = chat->num_clients;
        }

        werase(chat_win);
        mvwprintw(chat_win, 1, 1, "%s", chat->messages);
        wrefresh(chat_win);

        sleep(1);
    }

    return NULL;
}

int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);

    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        endwin();
        exit(1);
    }

    ChatRoom *chat = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (chat == MAP_FAILED) {
        perror("mmap");
        endwin();
        exit(1);
    }

    chat_win = newwin(20, 50, 0, 0);
    users_win = newwin(20, 20, 0, 50);
    input_win = newwin(3, 70, 20, 0);

    mvwprintw(input_win, 1, 1, "Enter your name: ");
    wrefresh(input_win);

    char name[32];
    wgetnstr(input_win, name, sizeof(name) - 1);

    // Увеличение количества клиентов
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    pthread_mutex_lock(&mutex);
    chat->num_clients++;
    pthread_mutex_unlock(&mutex);

    pthread_t tid;
    pthread_create(&tid, NULL, receive_messages, (void *)chat);

    while (1) {
        werase(input_win);
        mvwprintw(input_win, 1, 1, "%s: ", name);
        wrefresh(input_win);

        char msg[MSG_SIZE];
        wgetnstr(input_win, msg, sizeof(msg) - 1);

        int available_space = MSG_SIZE - strlen(name) - 3;
        if (strlen(msg) > available_space) {
            msg[available_space] = '\0';
        }

        snprintf(chat->messages, MSG_SIZE, "%s: %s", name, msg);
    }

    endwin();

    // Уменьшение количества клиентов при завершении работы
    pthread_mutex_lock(&mutex);
    chat->num_clients--;
    pthread_mutex_unlock(&mutex);

    munmap(chat, SHM_SIZE);
    close(shm_fd);

    return 0;
}