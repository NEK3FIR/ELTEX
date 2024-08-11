#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

int main() {
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARGS];
    char *token;
    pid_t pid;

    while (1) {
        printf("mybash> ");
        fgets(input, MAX_INPUT_SIZE, stdin);

        input[strcspn(input, "\n")] = 0; // Удаление символа новой строки

        if (strcmp(input, "exit") == 0) {
            break;
        }

        int arg_index = 0;
        token = strtok(input, " ");
        while (token != NULL) {
            args[arg_index++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_index] = NULL;

        pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            if (execvp(args[0], args) < 0) {
                perror("exec failed");
            }
            exit(1);
        } else {
            waitpid(pid, NULL, 0);
        }
    }

    return 0;
}
