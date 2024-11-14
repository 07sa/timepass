#include <stdio.h>
#include <stdbool.h>

int findPage(int frames[], int frameCount, int page) {
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == page)
            return i;
    }
    return -1;
}

int fifoPageReplacement(int pages[], int pageCount, int frameCount) {
    int frames[frameCount];
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;  // Initialize frames to empty
    }

    int pageFaults = 0;
    int index = 0;  // Points to the next frame to replace in FIFO order

    for (int i = 0; i < pageCount; i++) {
        int page = pages[i];

        // Check if page is already in frames
        if (findPage(frames, frameCount, page) == -1) {
            // Page fault occurs
            frames[index] = page;  // Replace the oldest page
            index = (index + 1) % frameCount;  // Move index to next frame in FIFO
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

    int pageFaults = fifoPageReplacement(pages, pageCount, frameCount);
    printf("Total number of page faults: %d\n", pageFaults);

    return 0;
}
