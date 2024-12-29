#include <stdio.h>
#include <string.h>
#include <limits.h>
int main()
{
    int no_of_blocks;
    printf("Enter the number of blocks: ");
    scanf("%d", &no_of_blocks);
    int blocks[no_of_blocks];
    printf("Enter the size of each block: \n");
    for (int i = 0; i < no_of_blocks; i++)
    {
        scanf("%d", &blocks[i]);
    }
    int no_of_processes;
    printf("Enter the number of processes: ");
    scanf("%d", &no_of_processes);
    int given_block[no_of_processes], process[no_of_processes];
    memset(given_block, -1, sizeof(int) * no_of_processes);
    printf("Enter the memory requirement of each process: \n");
    for (int i = 0; i < no_of_processes; i++)
    {
        scanf("%d", &process[i]);
    }
    for (int i = 0; i < no_of_processes; i++)
    {
        int minFragmentation = INT_MAX;
        int blockNo = -1;
        for (int j = 0; j < no_of_blocks; j++)
        {
            if (blocks[j] >= process[i])
            {
                if (minFragmentation > (blocks[j] - process[i]))
                {
                    minFragmentation = blocks[j] - process[i];
                    blockNo = j;
                }
            }
        }
        if (blockNo != -1)
        {
            given_block[i] = blockNo + 1;
            blocks[blockNo] = 0;
        }
    }
    for (int i = 0; i < no_of_processes; i++)
    {
        if (given_block[i] != -1)
        {
            printf("Memory block assigned to Process %d: %d\n", process[i], given_block[i]);
        }
        else
        {
            printf("No memory block could be assigned.\n");
        }
    }
}
// #include<stdio.h>
// #include<limits.h>
// #include<string.h>
// int main()
// {
//     int n, p;
//     printf("Enter no of free blocks available: ");
//     scanf("%d", &n);
//     int block[n];
//     printf("Enter the size of each block: ");
//     for(int i=0; i<n;i++)
//     {
//         scanf("%d", &block[i]);
//     }

//     printf("Enter no of processes: ");
//     scanf("%d", &p);
//     int memoryreq[p];
//     printf("Enter the memory requirement for each process : ");
//     for(int i=0; i<p;i++)
//     {
//         scanf("%d", &memoryreq[i]);
//     }

//     int assignblock[p];
//     memset(assignblock, -1, sizeof(assignblock));

// //best fit allocation
//     for(int i=0; i<p; i++)
//     {
//         int minfragmnetation = INT_MAX;
//         int block_no =-1;

//         // Find the best fit block for current process
//         for (int j= 0; j < n; j++)
//         {
//            if(memoryreq[i] <= block[j])
//            {
//             if((block[j] - memoryreq[i]) < minfragmnetation )
//             {
//                 minfragmnetation = block[j] - memoryreq[i];
//                 block_no = j;
//             }
//            }
//         }
// // Allocate the best fit block if found
//         if(block_no != -1)
//         {
//             assignblock[i] = block_no;
//             block[block_no] -=memoryreq[i];
//         }
//     }

//     // Output the allocation results
//     for (int i = 0; i < p; i++)
//     {
//         if (assignblock[i] != -1) {
//             printf("Process %d with memory requirement %d allocated to block %d\n", i + 1, memoryreq[i], assignblock[i] + 1);
//         }
//         else {
//             printf("Process %d with memory requirement %d could not be allocated\n", i + 1, memoryreq[i]);
//         }
//     }
//         return 0;
//     }