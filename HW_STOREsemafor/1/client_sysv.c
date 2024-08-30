// client_sysv.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024

int main() {
    // Generate unique key
    key_t key = ftok("shmfile", 65);

    // Get the shared memory segment
    int shmid = shmget(key, SHM_SIZE, 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach to the shared memory
    char *str = (char*) shmat(shmid, NULL, 0);
    if (str == (char*) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Read data from shared memory
    printf("Client: Message from server: %s\n", str);

    // Write response to shared memory
    strcpy(str, "Hello!");

    printf("Client: Response 'Hello!' written to shared memory.\n");

    // Detach from shared memory
    shmdt(str);

    return 0;
}
