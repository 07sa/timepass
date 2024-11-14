#include <stdio.h>
#include <stdbool.h>

void detectDeadlock(int processes[], int avail[], int allocation[][10], int request[][10], int n, int m) {
    bool finish[n];
    for (int i = 0; i < n; i++) {
        finish[i] = false;
    }

    int work[m];
    for (int i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    bool deadlock = false;
    int deadlockedProcesses[n], deadlockCount = 0;

    while (1) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < m; j++) {
                    if (request[i][j] > work[j]) {
                        break;
                    }
                }
                
                if (j == m) {
                    for (int k = 0; k < m; k++) {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            for (int i = 0; i < n; i++) {
                if (!finish[i]) {
                    deadlockedProcesses[deadlockCount++] = processes[i];
                    deadlock = true;
                }
            }
            break;
        }
    }

    if (deadlock) {
        printf("System is in deadlock. Deadlocked processes are: ");
        for (int i = 0; i < deadlockCount; i++) {
            printf("P%d ", deadlockedProcesses[i]);
        }
        printf("\n");
    } else {
        printf("No deadlock detected. System is in a safe state.\n");
    }
}

int main() {
    int n, m;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int processes[n];
    for (int i = 0; i < n; i++) {
        processes[i] = i;
    }

    int allocation[n][m];
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    int request[n][m];
    printf("Enter the request matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    int avail[m];
    printf("Enter the available resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    detectDeadlock(processes, avail, allocation, request, n, m);

    return 0;
}
