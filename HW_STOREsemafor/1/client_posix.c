// client_posix.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define SHM_NAME "/posix_shm_example"
#define SHM_SIZE 1024

int main() {
    // Open the shared memory object
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Map shared memory to the process's address space
    char *shm_ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Read the message from shared memory
    printf("Client: Message from server: %s\n", shm_ptr);

    // Write a response to shared memory
    sprintf(shm_ptr, "Hello!");

    printf("Client: Response 'Hello!' written to shared memory.\n");

    return 0;
}
