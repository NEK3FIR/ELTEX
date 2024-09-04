#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() {
    sigset_t set;

    // Инициализация пустого набора сигналов
    sigemptyset(&set);
    
    // Добавляем SIGINT в набор сигналов для блокировки
    sigaddset(&set, SIGINT);
    
    // Блокируем сигнал SIGINT
    if (sigprocmask(SIG_BLOCK, &set, NULL) == -1) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }

    printf("SIGINT is blocked. Running infinite loop...\n");

    // Бесконечный цикл
    while (1) {
        pause();  // Ожидание сигнала (любой другой)
    }

    return 0;
}
