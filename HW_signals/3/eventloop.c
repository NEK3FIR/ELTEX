#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

int main(void) 
{
    sigset_t set;
    int ret;
    int sig_num;

    // Инициализация пустого набора сигналов
    sigemptyset(&set);
    
    // Добавляем SIGINT в набор сигналов для блокировки
    sigaddset(&set, SIGUSR1);
    
    // Блокируем сигнал SIGINT
    ret = sigprocmask(SIG_BLOCK, &set, NULL);
    if (ret < 0) {
        perror("Can't ser signal handler!\n");
        exit(EXIT_FAILURE);
    }
    
    // Бесконечный цикл
    while (1) {
    sigwait(&set, &sig_num);
    printf("Sig number %d\n",sig_num);
    }

    return 0;
}
