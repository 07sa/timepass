#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

sem_t wrt;
pthread_mutex_t mutex;
int cnt = 1;
int numreader = 0;

void *writer(void *wno)
{   
    sem_wait(&wrt);  
    cnt = cnt * 2;
    printf("Writer %d modified cnt to %d\n", (*((int *)wno)), cnt);
    sem_post(&wrt);  
    return NULL;
}

void *reader(void *rno)
{   
    // Reader acquires the mutex before updating numreader count
    pthread_mutex_lock(&mutex);
    numreader++;
    if (numreader == 1) {
        sem_wait(&wrt); // First reader blocks the writer
    }
    pthread_mutex_unlock(&mutex);

    // Reading section
    printf("Reader %d: read cnt as %d\n", *((int *)rno), cnt);

    // Reader acquires the mutex again before decrementing numreader
    pthread_mutex_lock(&mutex);
    numreader--;
    if (numreader == 0) {
        sem_post(&wrt); // Last reader unblocks the writer
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main()
{
    int numReaders, numWriters;
    
    // Taking input from the user
    printf("Enter the number of readers: ");
    if (scanf("%d", &numReaders) != 1 || numReaders <= 0) {
        printf("Invalid input for number of readers.\n");
        return -1;
    }

    printf("Enter the number of writers: ");
    if (scanf("%d", &numWriters) != 1 || numWriters <= 0) {
        printf("Invalid input for number of writers.\n");
        return -1;
    }

    pthread_t readers[numReaders], writers[numWriters];
    int readerIds[numReaders], writerIds[numWriters];

    // Initialize mutex and semaphore
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);

    // Create reader threads
    for (int i = 0; i < numReaders; i++) {
        readerIds[i] = i + 1; // Assign IDs starting from 1
        if (pthread_create(&readers[i], NULL, reader, &readerIds[i]) != 0) {
            printf("Failed to create reader thread %d\n", i + 1);
        }
    }

    // Create writer threads
    for (int i = 0; i < numWriters; i++) {
        writerIds[i] = i + 1; // Assign IDs starting from 1
        if (pthread_create(&writers[i], NULL, writer, &writerIds[i]) != 0) {
            printf("Failed to create writer thread %d\n", i + 1);
        }
    }

    // Wait for all reader threads to complete
    for (int i = 0; i < numReaders; i++) {
        pthread_join(readers[i], NULL);
    }

    // Wait for all writer threads to complete
    for (int i = 0; i < numWriters; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy mutex and semaphore
    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    printf("All readers and writers have finished execution.\n");

    return 0;
}
