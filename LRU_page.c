#include <stdio.h>

int findLRU(int time[], int frameCount) {
    int min = time[0], pos = 0;
    for (int i = 1; i < frameCount; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int lruPageReplacement(int pages[], int pageCount, int frameCount) {
    int frames[frameCount], time[frameCount];
    int pageFaults = 0, counter = 0;

    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;  // Initialize frames as empty
    }

    for (int i = 0; i < pageCount; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page is already in a frame
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == page) {
                found = 1;
                time[j] = ++counter;  // Update the time for the page
                break;
            }
        }

        // If page is not found, replace the LRU page
        if (!found) {
            int pos = -1;

            // Find an empty frame
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // If no empty frame is found, replace the least recently used page
            if (pos == -1) {
                pos = findLRU(time, frameCount);
            }

            frames[pos] = page;
            time[pos] = ++counter;
            pageFaults++;
        }

        // Display current frame status
        printf("Frames: ");
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }
        printf("\n");
    }

    return pageFaults;
}

int main() {
    int pageCount, frameCount;

    printf("Enter the number of pages in the reference string: ");
    scanf("%d", &pageCount);
    int pages[pageCount];

    printf("Enter the reference string (space-separated): ");
    for (int i = 0; i < pageCount; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &frameCount);

    int pageFaults = lruPageReplacement(pages, pageCount, frameCount);
    printf("Total number of page faults: %d\n", pageFaults);

    return 0;
}
