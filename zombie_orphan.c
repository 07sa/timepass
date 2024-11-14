#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void createZombieProcess() {
    if (fork() == 0) { // Child process
        printf("Child process (Zombie) created with PID: %d\n", getpid());
        exit(0); // Child exits immediately, becoming a zombie process
    }
    // Parent sleeps to keep the zombie process alive for a while
    sleep(2);
}

void createOrphanProcess() {
    pid_t pid = fork();
    if (pid == 0) { // Child process
        sleep(5); // Sleep to allow parent to terminate first
        printf("Orphan child process with PID: %d, adopted by init process\n", getpid());
    } else if (pid > 0) { // Parent process
        printf("Parent process exiting before child (Creating Orphan)\n");
        exit(0); // Parent exits, orphaning the child process
    }
}

void sumEvenOddNumbers(int arr[], int n) {
    pid_t pid = fork();

    if (pid == 0) { // Child process
        int odd_sum = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] % 2 != 0) {
                odd_sum += arr[i];
            }
        }
        printf("Child process: Sum of odd numbers = %d\n", odd_sum);
        exit(0);
    } else if (pid > 0) { // Parent process
        int even_sum = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] % 2 == 0) {
                even_sum += arr[i];
            }
        }
        wait(NULL); // Wait for child process to complete
        printf("Parent process: Sum of even numbers = %d\n", even_sum);
    }
}

int main() {
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    printf("\nCreating a Zombie Process...\n");
    createZombieProcess();

    printf("\nCreating an Orphan Process...\n");
    createOrphanProcess();
    sleep(6); // Sleep to allow orphan child process to print message

    printf("\nCalculating Sum of Even and Odd Numbers:\n");
    sumEvenOddNumbers(arr, n);

    return 0;
}
