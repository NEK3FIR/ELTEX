#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *fifoPath = "/tmp/myfifo";

    // Открытие FIFO на чтение
    int fd = open(fifoPath, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char buffer[100];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
    if (bytesRead == -1) {
        perror("read");
        return 1;
    }

    // Завершение строки и вывод на экран
    buffer[bytesRead] = '\0';
    printf("Client read: %s\n", buffer);

    close(fd); // Закрываем дескриптор

    // Удаление FIFO
    if (unlink(fifoPath) == -1) {
        perror("unlink");
        return 1;
    }

    return 0;
}
