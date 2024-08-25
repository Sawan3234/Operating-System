#include <stdio.h>

int main() {
    int incomingStream[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int pageFaults = 0;
    int pageHits = 0;
    int frames;
    int m, n, s, pages;

    // Prompt user for the number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    printf("Incoming\t");
    // Print headers for the frames
    for (m = 1; m <= frames; m++) {
        printf("Frame %d\t", m);
    }
    printf("\n");

    pages = sizeof(incomingStream) / sizeof(incomingStream[0]);

    int temp[frames];
    for (m = 0; m < frames; m++) {
        temp[m] = -1;
    }

    for (m = 0; m < pages; m++) {
        s = 0;

        // Check if the page is already in one of the frames
        for (n = 0; n < frames; n++) {
            if (incomingStream[m] == temp[n]) {
                s = 1;  // Page hit
                pageHits++;
                break;
            }
        }

        // If page not found, it is a page fault
        if (s == 0) {
            pageFaults++;

            // Find an empty slot or use a page replacement strategy
            if (pageFaults <= frames) {
                temp[pageFaults - 1] = incomingStream[m];
            } else {
                temp[(pageFaults - 1) % frames] = incomingStream[m];
            }
        }

        // Print the current state of the frames
        printf("\n%d\t\t", incomingStream[m]);
        for (n = 0; n < frames; n++) {
            if (temp[n] != -1)
                printf(" %d\t", temp[n]);
            else
                printf(" - \t");
        }
    }

    printf("\n\nTotal Page Faults:\t%d\n", pageFaults);
    printf("Total Page Hits:\t%d\n", pageHits);

    return 0;
}
