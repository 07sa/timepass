#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

// States of each philosopher
#define THINKING 0
#define HUNGRY 1
#define EATING 2

sem_t mutex; // Mutex to protect critical section
sem_t forks[NUM_PHILOSOPHERS]; // Semaphore for each fork

int state[NUM_PHILOSOPHERS]; // Array to keep track of philosopher states
int philosophers[NUM_PHILOSOPHERS] = {0, 1, 2, 3, 4}; // Philosopher IDs

// Function to test if a philosopher can start eating
void test(int philosopher) {
    if (state[philosopher] == HUNGRY && 
        state[(philosopher + 4) % NUM_PHILOSOPHERS] != EATING && 
        state[(philosopher + 1) % NUM_PHILOSOPHERS] != EATING) {
        
        state[philosopher] = EATING;
        printf("Philosopher %d takes forks %d and %d and starts eating.\n", 
               philosopher + 1, philosopher + 1, (philosopher + 1) % NUM_PHILOSOPHERS + 1);
        
        // Signal the philosopher to start eating
        sem_post(&forks[philosopher]);
    }
}

// Function for a philosopher to pick up forks
void pick_up_forks(int philosopher) {
    sem_wait(&mutex); // Enter critical section
    
    state[philosopher] = HUNGRY;
    printf("Philosopher %d is hungry and tries to pick up forks.\n", philosopher + 1);
    
    test(philosopher); // Try to acquire forks
    
    sem_post(&mutex); // Exit critical section
    sem_wait(&forks[philosopher]); // Wait if forks are not available
    sleep(1); // Simulate eating time
}

// Function for a philosopher to put down forks
void put_down_forks(int philosopher) {
    sem_wait(&mutex); // Enter critical section

    state[philosopher] = THINKING;
    printf("Philosopher %d puts down forks %d and %d and starts thinking.\n", 
           philosopher + 1, philosopher + 1, (philosopher + 1) % NUM_PHILOSOPHERS + 1);
    
    // Test if neighboring philosophers can now eat
    test((philosopher + 4) % NUM_PHILOSOPHERS);
    test((philosopher + 1) % NUM_PHILOSOPHERS);
    
    sem_post(&mutex); // Exit critical section
}

// Function representing the philosopher's behavior
void* philosopher(void* num) {
    int philosopher = *(int *)num;

    while (1) {
        printf("Philosopher %d is thinking.\n", philosopher + 1);
        sleep(1); // Simulate thinking time
        
        pick_up_forks(philosopher);
        put_down_forks(philosopher);
    }
}

int main() {
    int i;
    pthread_t thread_id[NUM_PHILOSOPHERS];

    // Initialize the semaphores
    sem_init(&mutex, 0, 1);
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 0);
    }

    // Create philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &philosophers[i]);
        printf("Philosopher %d is sitting at the table.\n", i + 1);
    }

    // Wait for philosopher threads to finish (they don't in this example)
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(thread_id[i], NULL);
    }

    // Destroy the semaphores
    sem_destroy(&mutex);
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}
