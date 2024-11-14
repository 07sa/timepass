#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void SSTF_DiskScheduling(int requests[], int numRequests, int head) {
    int totalSeekTime = 0;
    int currentHead = head;
    bool visited[numRequests];

    // Initialize visited array to keep track of serviced requests
    for (int i = 0; i < numRequests; i++) {
        visited[i] = false;
    }

    printf("\nRequest\t\tCurrent Head\tSeek Time\n");
    printf("------------------------------------------\n");

    for (int i = 0; i < numRequests; i++) {
        int minSeekTime = __INT_MAX__;
        int nearestRequestIndex = -1;

        // Find the closest unvisited request to the current head
        for (int j = 0; j < numRequests; j++) {
            if (!visited[j]) {
                int seekTime = abs(requests[j] - currentHead);
                if (seekTime < minSeekTime) {
                    minSeekTime = seekTime;
                    nearestRequestIndex = j;
                }
            }
        }

        // Service the nearest request
        visited[nearestRequestIndex] = true;
        totalSeekTime += minSeekTime;
        
        printf("%d\t\t%d\t\t%d\n", requests[nearestRequestIndex], currentHead, minSeekTime);
        
        currentHead = requests[nearestRequestIndex];
    }

    printf("------------------------------------------\n");
    printf("Total Seek Time: %d\n", totalSeekTime);
}

int main() {
    int head, numRequests;

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    printf("Enter the number of disk requests: ");
    scanf("%d", &numRequests);

    int requests[numRequests];
    printf("Enter the disk requests (space-separated): ");
    for (int i = 0; i < numRequests; i++) {
        scanf("%d", &requests[i]);
    }

    printf("\nAccepted Input:\n");
    printf("Initial Head Position: %d\n", head);
    printf("Disk Requests: ");
    for (int i = 0; i < numRequests; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n");

    SSTF_DiskScheduling(requests, numRequests, head);

    return 0;
}
