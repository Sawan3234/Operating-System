#include <stdio.h>
void implimentBestFit(int blockSize[], int blocks, int processSize[], int processes)
{
   
    int allocation[processes];
    for(int i = 0; i < processes; i++){
        allocation[i] = -1;
    }
    for (int i=0; i<processes; i++)
    {
        
        int indexPlaced = -1;
        for (int j=0; j<blocks; j++) 
        { 
            if (blockSize[j] >= processSize[i])
            {
                 if (indexPlaced == -1)
                    indexPlaced = j;
                else if (blockSize[j] < blockSize[indexPlaced])
                    indexPlaced = j;
            }
        }
        if (indexPlaced != -1)
        {
            allocation[i] = indexPlaced;
            blockSize[indexPlaced] -= processSize[i];
        }
    }
 
    printf("\nProcess No. \t\tProcess Size   \t\tBlock no.\n");
    for (int i = 0; i < processes; i++)
    {
        printf("%d \t\t\t %d \t\t\t", i+1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n",allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}
int main()
{
    int blockSize[] = {50, 20, 100, 90};
    int processSize[] = {10, 30, 60, 110};
    int blocks = sizeof(blockSize)/sizeof(blockSize[0]);
    int processes = sizeof(processSize)/sizeof(processSize[0]);
    implimentBestFit(blockSize, blocks, processSize, processes);
    return 0 ;
}