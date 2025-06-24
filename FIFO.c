#include <stdio.h>

int main() {
    int incomingStream[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int pageFaults = 0;
    int pageHits = 0;
    int frames;
    int m, n, s, pages;
    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    printf("Incoming\t");
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
        for (n = 0; n < frames; n++) {
            if (incomingStream[m] == temp[n]) {
               s = 1;  
                pageHits++;
                break;
            }
        }
        if (s == 0) {
            pageFaults++;
            if (pageFaults <= frames) {
                temp[pageFaults - 1] = incomingStream[m];
            } else {
                temp[(pageFaults - 1) % frames] = incomingStream[m];
            }
        }
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
