#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PID>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid = atoi(argv[1]);

    // Посылка сигнала SIGUSR1 процессу с указанным PID
    if (kill(pid, SIGUSR1) == -1) {
        perror("kill");
        exit(EXIT_FAILURE);
    }

    printf("Sent SIGUSR1 signal to process %d\n", pid);

    return 0;
}
