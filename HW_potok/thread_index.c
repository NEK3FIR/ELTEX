// file: thread_index.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

void* print_index(void* arg) {
    int index = *(int*)arg;
    printf("Thread index: %d\n", index);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int indices[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        indices[i] = i;
        pthread_create(&threads[i], NULL, print_index, &indices[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
