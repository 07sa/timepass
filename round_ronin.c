#include <stdio.h>

void calculateTimes(int processes[], int n, int burstTime[], int quantum) {
    int waitingTime[n], turnaroundTime[n], remainingTime[n];
    int t = 0; // Current time

    // Copy burst times into remaining times
    for (int i = 0; i < n; i++)
        remainingTime[i] = burstTime[i];

    while (1) {
        int done = 1;

        for (int i = 0; i < n; i++) {
            if (remainingTime[i] > 0) {
                done = 0; // There is a pending process

                if (remainingTime[i] > quantum) {
                    t += quantum;
                    remainingTime[i] -= quantum;
                } else {
                    t += remainingTime[i];
                    waitingTime[i] = t - burstTime[i];
                    remainingTime[i] = 0;
                }
            }
        }

        if (done == 1)
            break;
    }

    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++)
        turnaroundTime[i] = burstTime[i] + waitingTime[i];

    // Display times for each process
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\n", processes[i], burstTime[i], waitingTime[i], turnaroundTime[i]);
    }

    // Calculate average waiting and turnaround times
    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        totalWT += waitingTime[i];
        totalTAT += turnaroundTime[i];
    }

    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTAT / n);
}

int main() {
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], burstTime[n];

    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &burstTime[i]);
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    calculateTimes(processes, n, burstTime, quantum);

    return 0;
}
