#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>

#define SHM_NAME "/chat_shm"
#define SHM_SIZE 4096
#define MSG_SIZE 256
#define MAX_CLIENTS 10

typedef struct {
    int num_clients;
    char messages[SHM_SIZE - sizeof(int)];
} ChatRoom;

int main() {
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    if (ftruncate(shm_fd, SHM_SIZE) == -1) {
        perror("ftruncate");
        exit(1);
    }

    ChatRoom *chat = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (chat == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    chat->num_clients = 0;
    memset(chat->messages, 0, sizeof(chat->messages));

    printf("Сервер запущен. Ожидание клиентов...\n");

    while (1) {
        if (chat->num_clients > 0) {
            printf("Waiting for new messages...\n");

            if (strlen(chat->messages) > 0) {
                printf("Новое сообщение: %s\n", chat->messages);
                memset(chat->messages, 0, sizeof(chat->messages));
            }
        }

        sleep(1);
    }

    munmap(chat, SHM_SIZE);
    close(shm_fd);
    shm_unlink(SHM_NAME);

    return 0;
}
