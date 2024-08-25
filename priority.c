#include <stdio.h>

int main() {
    int burstTime[20], process[20], waitingTime[20], turnaroundTime[20], priority[20];
    int i, j, numProcesses, totalWaitTime = 0, pos, temp;
    float avgWaitTime, avgTurnaroundTime;
    printf("Enter Total Number of Processes: ");
    scanf("%d", &numProcesses);
    printf("\nEnter Burst Time and Priority for each process:\n");
    for (i = 0; i < numProcesses; i++) {
        printf("Process P[%d]:\n", i + 1);
        printf("Burst Time: ");
        scanf("%d", &burstTime[i]);
        printf("Priority: ");
        scanf("%d", &priority[i]);
        process[i] = i + 1;  // Store process ID
    }
    for (i = 0; i < numProcesses - 1; i++) {
        pos = i;
        for (j = i + 1; j < numProcesses; j++) {
            if (priority[j] < priority[pos]) {
                pos = j;
            }
        }
        temp = priority[i];
        priority[i] = priority[pos];
        priority[pos] = temp;
 
        temp = burstTime[i];
        burstTime[i] = burstTime[pos];
        burstTime[pos] = temp;

        temp = process[i];
        process[i] = process[pos];
        process[pos] = temp;
    }

    waitingTime[0] = 0;
    for (i = 1; i < numProcesses; i++) {
        waitingTime[i] = 0;
        for (j = 0; j < i; j++) {
            waitingTime[i] += burstTime[j];
        }
        totalWaitTime += waitingTime[i];
    }
    avgWaitTime = (float)totalWaitTime / numProcesses;

  
    totalWaitTime = 0;
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < numProcesses; i++) {
        turnaroundTime[i] = burstTime[i] + waitingTime[i];
        totalWaitTime += turnaroundTime[i];
        printf("P[%d]\t%d\t\t%d\t\t%d\n", process[i], burstTime[i], waitingTime[i], turnaroundTime[i]);
    }
    avgTurnaroundTime = (float)totalWaitTime / numProcesses;

    printf("\nAverage Waiting Time = %.3f", avgWaitTime);
    printf("\nAverage Turnaround Time = %.3f\n", avgTurnaroundTime);

    return 0;
}
