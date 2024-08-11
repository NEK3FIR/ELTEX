#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

void execute_command(char *input) {
    char *args[MAX_ARGS];
    char *token;
    int arg_index = 0;

    token = strtok(input, " ");
    while (token != NULL) {
        args[arg_index++] = token;
        token = strtok(NULL, " ");
    }
    args[arg_index] = NULL;

    if (execvp(args[0], args) < 0) {
        perror("exec failed");
        exit(1);
    }
}

int main() {
    char input[MAX_INPUT_SIZE];
    char *commands[MAX_ARGS];
    char *command;
    int pipe_fd[2];
    pid_t pid;
    int i;

    while (1) {
        printf("mybash> ");
        fgets(input, MAX_INPUT_SIZE, stdin);

        input[strcspn(input, "\n")] = 0; // Удаление символа новой строки

        if (strcmp(input, "exit") == 0) {
            break;
        }

        int cmd_index = 0;
        command = strtok(input, "|");
        while (command != NULL) {
            commands[cmd_index++] = command;
            command = strtok(NULL, "|");
        }
        commands[cmd_index] = NULL;

        int in_fd = 0;  // Входной файловый дескриптор для первой команды

        for (i = 0; i < cmd_index; i++) {
            pipe(pipe_fd);

            pid = fork();
            if (pid < 0) {
                perror("fork failed");
                exit(1);
            } else if (pid == 0) {
                dup2(in_fd, 0); // Подключаем стандартный ввод к in_fd
                if (i < cmd_index - 1) {
                    dup2(pipe_fd[1], 1); // Подключаем стандартный вывод к pipe_fd[1]
                }
                close(pipe_fd[0]);
                execute_command(commands[i]);
                exit(1);
            } else {
                waitpid(pid, NULL, 0);
                close(pipe_fd[1]);
                in_fd = pipe_fd[0];  // Стандартный ввод для следующей команды
            }
        }
    }

    return 0;
}
