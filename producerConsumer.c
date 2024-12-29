#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#define MaxItems 5   // Maximum items a producer can produce or a consumer can consume
#define BufferSize 5 // Size of the buffer
int buffer[BufferSize];
int in = 0;
int out = 0;
int itemCount = 0; // Counter to keep track of items in the buffer
// Semaphores for synchronization
sem_t empty; // Tracks empty slots in the buffer
sem_t full;  // Tracks full slots in the buffer
sem_t mutex; // Mutex to protect critical section
// Function to simulate producing an item
int produceItem()
{
    return rand() % 100; // Produces a random item between 0 and 99
}
// Function to insert an item into the buffer
void insertItem(int item)
{
    buffer[in] = item;
    in = (in + 1) % BufferSize;
    itemCount++;
}
// Function to remove an item from the buffer
int removeItem()
{
    int item = buffer[out];
    out = (out + 1) % BufferSize;
    itemCount--;
    return item;
}
void *producer(void *arg)
{
    int id = (int)arg;
    for (int i = 0; i < MaxItems; i++)
    {
        int item = produceItem();
        sem_wait(&empty); // Wait until there is space in the buffer
        sem_wait(&mutex); // Enter critical section (lock)
        insertItem(item); // Insert the item into the buffer
        printf("Producer %d: Insert Item %d at %d\n", id, item, in - 1);
        sem_post(&mutex); // Leave critical section (unlock)
        sem_post(&full);  // Signal that there is a new item in the buffer
        usleep(100000);   // Simulate some delay
    }
    printf("Producer %d done.\n", id);
    return NULL;
}
void *consumer(void *arg)
{
    int id = (int)arg;
    for (int i = 0; i < MaxItems; i++)
    {
        sem_wait(&full);         // Wait until there is an item to consume
        sem_wait(&mutex);        // Enter critical section (lock)
        int item = removeItem(); // Remove the item from the buffer
        printf("Consumer %d: Remove Item %d from %d\n", id, item, out - 1);
        sem_post(&mutex); // Leave critical section (unlock)
        sem_post(&empty); // Signal that there is space in the buffer
        usleep(150000);   // Simulate some delay
    }
    printf("Consumer %d done.\n", id);
    return NULL;
}
int main()
{
    sem_init(&empty, 0, BufferSize); // Initially, all buffer slots are empty
    sem_init(&full, 0, 0);           // Initially, there are no full slots
    sem_init(&mutex, 0, 1);          // Mutex is available for synchronization
    pthread_t producerThreads[5], consumerThreads[5];
    int producerIds[5] = {1, 2, 3, 4, 5};
    int consumerIds[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&producerThreads[i], NULL, producer, &producerIds[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&consumerThreads[i], NULL, consumer, &consumerIds[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(producerThreads[i], NULL);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(consumerThreads[i], NULL);
    }
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    printf("All threads finished. Exiting program.\n");
}