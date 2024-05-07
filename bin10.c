#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 5

int shared_variable = 0;
pthread_mutex_t mutex;
sem_t semaphore;

void* increment_shared_variable(void* arg) {
    int thread_id = *((int*)arg);

    // Using mutex to protect shared_variable
    pthread_mutex_lock(&mutex);
    shared_variable++;
    printf("Thread %d incremented shared variable to %d\n", thread_id, shared_variable);
    pthread_mutex_unlock(&mutex);

    // Using semaphore to synchronize threads
    sem_wait(&semaphore);
    printf("Thread %d entered critical section\n", thread_id);
    sleep(1); // Simulate critical section
    printf("Thread %d exited critical section\n", thread_id);
    sem_post(&semaphore);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Initialize semaphore
    sem_init(&semaphore, 0, 1);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, increment_shared_variable, (void*)&thread_ids[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy mutex
    pthread_mutex_destroy(&mutex);

    // Destroy semaphore
    sem_destroy(&semaphore);

    return 0;
}
































/*
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define BUFFER_SIZE 5
sem_t mutex, empty, full;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;
void *producer(void *arg) {
int item;
while (1) {
item = rand() % 100; // Generate a random item to produce
sem_wait(&empty);
sem_wait(&mutex);
buffer[in] = item;
printf("Produced: %d\n", item);
in = (in + 1) % BUFFER_SIZE;
sem_post(&mutex);
sem_post(&full);
sleep(rand() % 3); // Simulate some processing time
}
}
void *consumer(void *arg) {
int item;
while (1) {
sem_wait(&full);
sem_wait(&mutex);
item = buffer[out];
printf("Consumed: %d\n", item);
out = (out + 1) % BUFFER_SIZE;
sem_post(&mutex);
sem_post(&empty);
sleep(rand() % 3); // Simulate some processing time
}
}
int main() {
pthread_t producer_thread, consumer_thread;
// Initialize semaphores
sem_init(&mutex, 0, 1);
sem_init(&empty, 0, BUFFER_SIZE);
sem_init(&full, 0, 0);
// Create producer and consumer threads
pthread_create(&producer_thread, NULL, producer, NULL);
pthread_create(&consumer_thread, NULL, consumer, NULL);
// Join threads
pthread_join(producer_thread, NULL);
pthread_join(consumer_thread, NULL);
// Destroy semaphores
sem_destroy(&mutex);
sem_destroy(&empty);
sem_destroy(&full);
return 0;
}

*/
