#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        // Ошибка при создании процесса
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Дочерний процесс
        printf("Child: PID = %d, PPID = %d\n", getpid(), getppid());
        exit(0);
    } else {
        // Родительский процесс
        int status;
        printf("Parent: PID = %d, Child PID = %d\n", getpid(), pid);
        waitpid(pid, &status, 0);  // Ожидание завершения дочернего процесса
        printf("Child exit status = %d\n", WEXITSTATUS(status));
    }

    return 0;
}
