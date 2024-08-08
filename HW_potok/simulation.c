// file: simulation.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_SHOPS 5
#define NUM_CUSTOMERS 3
#define NUM_LOADERS 1
#define SHOP_CAPACITY 10000
#define CUSTOMER_NEED_LIMIT 100000
#define LOADER_LOAD 5000

pthread_mutex_t shop_mutexes[NUM_SHOPS];
int shops[NUM_SHOPS];

typedef struct {
    int need;
} customer_data_t;

typedef struct {
    int shop_index;
} loader_data_t;

void* customer(void* arg) {
    customer_data_t* data = (customer_data_t*)arg;
    int need = data->need;
    free(data);

    while (need > 0) {
        int shop_index = -1;

        for (int i = 0; i < NUM_SHOPS; i++) {
            if (pthread_mutex_trylock(&shop_mutexes[i]) == 0) {
                shop_index = i;
                break;
            }
        }

        if (shop_index != -1) {
            int shop_size = shops[shop_index];
            int purchase_amount = (need < shop_size) ? need : shop_size;
            shops[shop_index] -= purchase_amount;
            need -= purchase_amount;
            printf("Customer: Entered shop %d with need %d, purchased %d. Need now %d.\n",
                   shop_index, need + purchase_amount, purchase_amount, need);
            pthread_mutex_unlock(&shop_mutexes[shop_index]);
            sleep(2);
        } else {
            sleep(1);
        }
    }
    printf("Customer satisfied and exiting.\n");
    return NULL;
}

void* loader(void* arg) {
    loader_data_t* data = (loader_data_t*)arg;
    int shop_index = data->shop_index;
    free(data);

    while (1) {
        pthread_mutex_lock(&shop_mutexes[shop_index]);
        shops[shop_index] += LOADER_LOAD;
        printf("Loader: Refilled shop %d with %d. Current size %d.\n", shop_index, LOADER_LOAD, shops[shop_index]);
        pthread_mutex_unlock(&shop_mutexes[shop_index]);
        sleep(1);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t customer_threads[NUM_CUSTOMERS];
    pthread_t loader_threads[NUM_LOADERS];
    int num_customers_satisfied = 0;
    
    for (int i = 0; i < NUM_SHOPS; i++) {
        shops[i] = rand() % SHOP_CAPACITY;
        pthread_mutex_init(&shop_mutexes[i], NULL);
    }

    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        customer_data_t* data = (customer_data_t*)malloc(sizeof(customer_data_t));
        data->need = rand() % CUSTOMER_NEED_LIMIT;
        pthread_create(&customer_threads[i], NULL, customer, data);
    }

    for (int i = 0; i < NUM_LOADERS; i++) {
        loader_data_t* data = (loader_data_t*)malloc(sizeof(loader_data_t));
        data->shop_index = rand() % NUM_SHOPS;
        pthread_create(&loader_threads[i], NULL, loader, data);
    }

    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        pthread_join(customer_threads[i], NULL);
        num_customers_satisfied++;
    }

    for (int i = 0; i < NUM_LOADERS; i++) {
        pthread_cancel(loader_threads[i]);
        pthread_join(loader_threads[i], NULL);
    }

    for (int i = 0; i < NUM_SHOPS; i++) {
        pthread_mutex_destroy(&shop_mutexes[i]);
    }

    printf("All customers are satisfied. Program exiting.\n");
    return 0;
}
