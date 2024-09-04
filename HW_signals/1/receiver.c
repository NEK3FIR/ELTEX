#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Обработчик сигнала SIGUSR1
void sigusr1_handler(int signum) {
    printf("Received SIGUSR1 signal\n");
}

int main() {
    struct sigaction sa;

    // Установка обработчика сигнала
    sa.sa_handler = sigusr1_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for SIGUSR1 signal...\n");

    // Бесконечный цикл ожидания сигнала
    while (1) {
        pause();  // Ожидание сигнала
    }

    return 0;
}
