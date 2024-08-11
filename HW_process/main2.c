#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void create_process_and_wait(const char* name, int num_children) {
    pid_t pid;

    for (int i = 0; i < num_children; i++) {
        pid = fork();

        if (pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            printf("%s Child %d: PID = %d, PPID = %d\n", name, i + 1, getpid(), getppid());
            if (i < 2 && num_children == 2) {
                create_process_and_wait("Process1", 2); // Process3 и Process4
            }
            exit(0);
        }
    }

    for (int i = 0; i < num_children; i++) {
        wait(NULL);
    }

    printf("%s: PID = %d завершен.\n", name, getpid());
}

int main() {
    pid_t pid1, pid2;

    pid1 = fork();

    if (pid1 < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid1 == 0) {
        printf("Process1: PID = %d, PPID = %d\n", getpid(), getppid());
        create_process_and_wait("Process1", 2); // Process3 и Process4
        exit(0);
    }

    pid2 = fork();

    if (pid2 < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid2 == 0) {
        printf("Process2: PID = %d, PPID = %d\n", getpid(), getppid());
        create_process_and_wait("Process2", 1); // Process5
        exit(0);
    }

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    printf("Main Process: All child processes are completed.\n");

    return 0;
}
