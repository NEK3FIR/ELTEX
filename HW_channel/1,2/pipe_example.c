#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[100];

    // Создание неименованного канала
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // Создание дочернего процесса
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) { // Дочерний процесс
        close(pipefd[1]); // Закрываем дескриптор записи

        // Считываем из канала
        ssize_t bytesRead = read(pipefd[0], buffer, sizeof(buffer));
        if (bytesRead == -1) {
            perror("read");
            return 1;
        }

        // Завершаем строку и выводим на экран
        buffer[bytesRead] = '\0';
        printf("Child process read: %s\n", buffer);

        close(pipefd[0]); // Закрываем дескриптор чтения
    } else { // Родительский процесс
        close(pipefd[0]); // Закрываем дескриптор чтения

        // Записываем в канал
        const char *message = "Hi!";
        if (write(pipefd[1], message, strlen(message)) == -1) {
            perror("write");
            return 1;
        }

        close(pipefd[1]); // Закрываем дескриптор записи

        // Ожидание завершения дочернего процесса
        wait(NULL);
    }

    return 0;
}
