// server_sysv.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main() {
    // Generate unique key
    key_t key = ftok("shmfile", 65);

    // Create shared memory segment
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
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

    // Write data to shared memory
    strcpy(str, "Hi!");

    printf("Server: Message 'Hi!' written to shared memory.\n");
    printf("Server: Waiting for client response...\n");

    // Wait for the client to write back
    while (strcmp(str, "Hello!") != 0) {
        sleep(1);
    }

    printf("Server: Received message from client: %s\n", str);

    // Detach from shared memory
    shmdt(str);

    // Destroy the shared memory
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
