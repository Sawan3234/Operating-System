#include <stdio.h>
#include <limits.h>

int checkHit(int incomingPage, int queue[], int occupied) {
    for (int i = 0; i < occupied; i++) {
        if (incomingPage == queue[i])
            return 1;
    }
    return 0;
}

void printFrame(int queue[], int frames) {
    for (int i = 0; i < frames; i++) {
        if (i < frames)
            printf("%d\t\t", queue[i]);
        else
            printf("-\t\t"); 
    }
}

int main() {
    int incomingStream[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int n = sizeof(incomingStream) / sizeof(incomingStream[0]);

    int frames;
    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    int queue[frames];
    int distance[frames];
    int occupied = 0;
    int pagefault = 0;
    int pagehit = 0;

    for (int i = 0; i < frames; i++) {
        queue[i] = -1;
    }

    printf("Stream\t\t");
    for (int i = 0; i < frames; i++)
        printf("Frame%d\t\t", i + 1);
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%d:  \t\t", incomingStream[i]);

        if (checkHit(incomingStream[i], queue, occupied)) {
            printFrame(queue, frames);
            pagehit++;
        } else if (occupied < frames) {
            queue[occupied] = incomingStream[i];
            pagefault++;
            occupied++;
            printFrame(queue, occupied);
        } else {
            int max = INT_MIN;
            int index;

            for (int j = 0; j < frames; j++) {
                distance[j] = 0;

                for (int k = i - 1; k >= 0; k--) {
                    ++distance[j];
                    if (queue[j] == incomingStream[k])
                        break;
                }

                if (distance[j] > max) {
                    max = distance[j];
                    index = j;
                }
            }
            queue[index] = incomingStream[i];
            printFrame(queue, frames);
            pagefault++;
        }

        printf("\n");
    }

    printf("Page Faults: %d\n", pagefault);
    printf("Page Hits: %d\n", pagehit);

    return 0;
}
