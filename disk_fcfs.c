#include <stdio.h>
#include <stdlib.h>

void FCFS_DiskScheduling(int requests[], int numRequests, int head) {
    int totalSeekTime = 0;
    int currentHead = head;

    printf("\nRequest\t\tCurrent Head\tSeek Time\n");
    printf("------------------------------------------\n");

    for (int i = 0; i < numRequests; i++) {
        int seekTime = abs(requests[i] - currentHead);
        totalSeekTime += seekTime;
        
        printf("%d\t\t%d\t\t%d\n", requests[i], currentHead, seekTime);
        
        currentHead = requests[i];
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

    FCFS_DiskScheduling(requests, numRequests, head);

    return 0;
}
