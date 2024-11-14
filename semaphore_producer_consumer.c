#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define MIN_DELAY 1000  
#define MAX_DELAY 1000000  

// Global variables
int MaxItems;      
int BufferSize;    
sem_t empty;       
sem_t full;        
int in = 0, out = 0;   
int *buffer;       
pthread_mutex_t mutex;


void random_delay() {
    int delay = rand() % (MAX_DELAY - MIN_DELAY + 1) + MIN_DELAY;
    usleep(delay);  
}


void display_buffer() {
    printf("[Buffer]: ");
    for (int i = 0; i < BufferSize; i++) {
        if (i == in && i == out)
            printf("I/O ");
        else if (i == in)
            printf(" I  ");
        else if (i == out)
            printf(" O  ");
        else
            printf("[%d] ", buffer[i]);
    }
    printf("\n");
}

// Producer function
void *producer(void *pno) {
    int id = *((int *)pno);
    int item;
    for (int i = 0; i < MaxItems; i++) {
        random_delay();
        item = rand() % 100; // Produce a random item (0-99)
        sem_wait(&empty);    // Wait if buffer is full
        pthread_mutex_lock(&mutex); // Lock buffer

        buffer[in] = item;
        printf("Producer %d: Insert Item %d at %d\n", id, buffer[in], in);
        in = (in + 1) % BufferSize;

        display_buffer(); // Show buffer status

        pthread_mutex_unlock(&mutex); // Unlock buffer
        sem_post(&full);   // Signal that buffer has at least one full slot
    }
}

// Consumer function
void *consumer(void *cno) {
    int id = *((int *)cno);
    int item;
    for (int i = 0; i < MaxItems; i++) {
        random_delay();
        sem_wait(&full);    // Wait if buffer is empty
        pthread_mutex_lock(&mutex); // Lock buffer

        item = buffer[out];
        printf("Consumer %d: Remove Item %d from %d\n", id, item, out);
        out = (out + 1) % BufferSize;

        display_buffer(); // Show buffer status

        pthread_mutex_unlock(&mutex); // Unlock buffer
        sem_post(&empty);  
    }
}


void take_input(const char *prompt, int *var) {
    do {
        printf("%s", prompt);
        scanf("%d", var);
        if (*var <= 0)
            printf("Please enter a positive integer.\n");
    } while (*var <= 0);
}

// Main function
int main() {
    srand(time(NULL)); /

    int numProducers, numConsumers;

    take_input("Enter the number of producers: ", &numProducers);
    take_input("Enter the number of consumers: ", &numConsumers);
    take_input("Enter the size of the buffer: ", &BufferSize);
    take_input("Enter the number of items each producer/consumer can handle: ", &MaxItems);

    
    buffer = (int *)malloc(BufferSize * sizeof(int));

    pthread_t pro[numProducers], con[numConsumers];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BufferSize);
    sem_init(&full, 0, 0);

    int producerIds[numProducers], consumerIds[numConsumers];

    
    clock_t start = clock();

    // Create producer and consumer threads
    for (int i = 0; i < numProducers; i++) {
        producerIds[i] = i + 1;
        pthread_create(&pro[i], NULL, producer, (void *)&producerIds[i]);
    }
    for (int i = 0; i < numConsumers; i++) {
        consumerIds[i] = i + 1;
        pthread_create(&con[i], NULL, consumer, (void *)&consumerIds[i]);
    }

    // Wait for all producers and consumers to finish
    for (int i = 0; i < numProducers; i++) {
        pthread_join(pro[i], NULL);
    }
    for (int i = 0; i < numConsumers; i++) {
        pthread_join(con[i], NULL);
    }

    // End timing
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %.2f seconds\n", time_taken);

    // Clean up
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    free(buffer);

    return 0;
}

