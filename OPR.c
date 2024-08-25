#include <stdio.h>

// Function to check if a page is already in one of the frames
int isPageInFrames(int page, int frames[], int numFrames) {
    for (int i = 0; i < numFrames; i++) {
        if (frames[i] == page) {
            return 1;  // Page hit
        }
    }
    return 0;  // Page fault
}

// Function to print the headers for frames
void printFrameHeaders(int numFrames) {
    printf("Stream\t");
    for (int i = 0; i < numFrames; i++) {
        printf("Frame%d\t", i + 1);
    }
    printf("\n");
}

// Function to print the current state of the frames
void printFrames(int page, int frames[], int numFrames, int occupiedFrames) {
    printf("%d\t", page);
    for (int i = 0; i < numFrames; i++) {
        if (i < occupiedFrames) {
            printf("%d\t", frames[i]);
        } else {
            printf("-\t");
        }
    }
    printf("\n");
}

// Function to find the optimal frame to replace
int findFrameToReplace(int refStr[], int frames[], int refStrLen, int currentIndex, int numFrames) {
    int farthest = currentIndex;
    int frameToReplace = 0;

    for (int i = 0; i < numFrames; i++) {
        int j;
        for (j = currentIndex; j < refStrLen; j++) {
            if (frames[i] == refStr[j]) {
                if (j > farthest) {
                    farthest = j;
                    frameToReplace = i;
                }
                break;
            }
        }
        if (j == refStrLen) {
            return i;  // This frame is never referenced again
        }
    }
    return frameToReplace;
}

// Function to simulate the Optimal Page Replacement algorithm
void optimalPageReplacement(int refStr[], int refStrLen, int numFrames) {
    int frames[numFrames];
    int occupiedFrames = 0;
    int pageHits = 0;

    // Initialize frames with -1 to indicate they are empty
    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1;
    }

    printFrameHeaders(numFrames);

    for (int i = 0; i < refStrLen; i++) {
        int page = refStr[i];

        if (isPageInFrames(page, frames, occupiedFrames)) {
            pageHits++;
            printFrames(page, frames, numFrames, occupiedFrames);
        } else {
            if (occupiedFrames < numFrames) {
                frames[occupiedFrames] = page;
                occupiedFrames++;
            } else {
                int frameToReplace = findFrameToReplace(refStr, frames, refStrLen, i + 1, numFrames);
                frames[frameToReplace] = page;
            }
            printFrames(page, frames, numFrames, occupiedFrames);
        }
    }

    printf("\nPage Hits: %d\n", pageHits);
    printf("Page Faults: %d\n", refStrLen - pageHits);
}

// Main function
int main() {
    int refStr[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int refStrLen = sizeof(refStr) / sizeof(refStr[0]);

    int numFrames;
    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);

    optimalPageReplacement(refStr, refStrLen, numFrames);

    return 0;
}