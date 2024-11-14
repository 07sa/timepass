#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void SCAN_DiskScheduling(int requests[], int numRequests, int head, int diskSize, int direction) {
    int totalSeekTime = 0;
    int currentHead = head;
    
    // Add head position and disk endpoints (0 and diskSize-1) to the requests
    int extendedRequests[numRequests + 2];
    for (int i = 0; i < numRequests; i++) {
        extendedRequests[i] = requests[i];
    }
    extendedRequests[numRequests] = 0;
    extendedRequests[numRequests + 1] = diskSize - 1;

    // Sort the requests array
    sort(extendedRequests, numRequests + 2);

    // Find the position of the current head in the sorted array
    int headIndex;
    for (int i = 0; i < numRequests + 2; i++) {
        if (extendedRequests[i] == head) {
            headIndex = i;
            break;
        }
    }

    printf("\nRequest\t\tCurrent Head\tSeek Time\n");
    printf("------------------------------------------\n");

    // Service requests in the selected direction
    if (direction == 1) { // Moving towards the end (right)
        for (int i = headIndex; i < numRequests + 2; i++) {
            int seekTime = abs(extendedRequests[i] - currentHead);
            totalSeekTime += seekTime;
            printf("%d\t\t%d\t\t%d\n", extendedRequests[i], currentHead, seekTime);
            currentHead = extendedRequests[i];
        }
        for (int i = headIndex - 1; i >= 0; i--) {
            int seekTime = abs(extendedRequests[i] - currentHead);
            totalSeekTime += seekTime;
            printf("%d\t\t%d\t\t%d\n", extendedRequests[i], currentHead, seekTime);
            currentHead = extendedRequests[i];
        }
    } else { // Moving towards the start (left)
        for (int i = headIndex; i >= 0; i--) {
            int seekTime = abs(extendedRequests[i] - currentHead);
            totalSeekTime += seekTime;
            printf("%d\t\t%d\t\t%d\n", extendedRequests[i], currentHead, seekTime);
            currentHead = extendedRequests[i];
        }
        for (int i = headIndex + 1; i < numRequests + 2; i++) {
            int seekTime = abs(extendedRequests[i] - currentHead);
            totalSeekTime += seekTime;
            printf("%d\t\t%d\t\t%d\n", extendedRequests[i], currentHead, seekTime);
            currentHead = extendedRequests[i];
        }
    }

    printf("------------------------------------------\n");
    printf("Total Seek Time: %d\n", totalSeekTime);
}

int main() {
    int head, numRequests, diskSize, direction;

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    printf("Enter the number of disk requests: ");
    scanf("%d", &numRequests);

    int requests[numRequests];
    printf("Enter the disk requests (space-separated): ");
    for (int i = 0; i < numRequests; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the disk size: ");
    scanf("%d", &diskSize);

    printf("Enter the initial direction (1 for right/end, 0 for left/start): ");
    scanf("%d", &direction);

    printf("\nAccepted Input:\n");
    printf("Initial Head Position: %d\n", head);
    printf("Disk Requests: ");
    for (int i = 0; i < numRequests; i++) {
        printf("%d ", requests[i]);
    }
    printf("\nDisk Size: %d\n", diskSize);
    printf("Initial Direction: %s\n", direction ? "Right" : "Left");

    SCAN_DiskScheduling(requests, numRequests, head, diskSize, direction);

    return 0;
}
