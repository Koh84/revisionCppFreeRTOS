#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t empty;   // counts empty slots
sem_t full;    // counts full slots
int buffer[1]; // single-item buffer for simplicity

void* producer(void* arg) {
    int item = 42;
    sem_wait(&empty);      // wait for empty slot
    buffer[0] = item;      // produce
    sem_post(&full);       // signal full slot
    return NULL;
}

void* consumer(void* arg) {
    sem_wait(&full);       // wait for full slot
    int item = buffer[0];  // consume
    printf("Consumed: %d\n", item);
    sem_post(&empty);      // signal empty slot
    return NULL;
}

int main() {
    pthread_t p, c;
    sem_init(&empty, 0, 1);  // 1 empty slot
    sem_init(&full, 0, 0);   // 0 full slots

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}
