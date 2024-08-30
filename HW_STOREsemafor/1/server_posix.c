// server_posix.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define SHM_NAME "/posix_shm_example"
#define SHM_SIZE 1024

int main() {
    // Create shared memory object
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Set size of the shared memory
    if (ftruncate(shm_fd, SHM_SIZE) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    // Map shared memory to the process's address space
    char *shm_ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Write a message to shared memory
    sprintf(shm_ptr, "Hi!");

    printf("Server: Message 'Hi!' written to shared memory.\n");
    printf("Server: Waiting for client response...\n");

    // Wait for the client to write back
    while (strcmp(shm_ptr, "Hello!") != 0) {
        sleep(1);
    }

    printf("Server: Received message from client: %s\n", shm_ptr);

    // Clean up
    if (shm_unlink(SHM_NAME) == -1) {
        perror("shm_unlink");
        exit(EXIT_FAILURE);
    }

    return 0;
}
