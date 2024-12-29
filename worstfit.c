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
        int maxFragmentation = INT_MIN;
        int blockNo = -1;
        for (int j = 0; j < no_of_blocks; j++)
        {
            if (blocks[j] >= process[i])
            {
                if (maxFragmentation < (blocks[j] - process[i]))
                {
                    maxFragmentation = blocks[j] - process[i];
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
            printf("%d: No memory block could be assigned.\n", process[i]);
        }
    }
}

// Enter number of free blocks available : 5
//  100 500 200 300 600
//  Enter number of processes : 4
//  212 417 112 426
//  212 – 5
//  417 - 2
//  112 - 4
//  426 – no free block allocated
//  #include <stdio.h>
//  #include <limits.h>
//  #include <string.h>

// int main() {
//     int n, p;

//     // Input number of blocks and their sizes
//     printf("Enter number of free blocks available: ");
//     scanf("%d", &n);
//     int block[n], originalBlock[n];
//     printf("Enter the size of each block: ");
//     for (int i = 0; i < n; i++) {
//         scanf("%d", &block[i]);
//         originalBlock[i] = block[i]; // Keep a copy of the original sizes
//     }

//     // Input number of processes and their memory requirements
//     printf("Enter number of processes: ");
//     scanf("%d", &p);
//     int memoryreq[p];
//     printf("Enter the memory requirement for each process: ");
//     for (int i = 0; i < p; i++) {
//         scanf("%d", &memoryreq[i]);
//     }

//     // Array to store which block each process is assigned to (-1 = not allocated)
//     int assignblock[p];
//     memset(assignblock, -1, sizeof(assignblock));

//     // Worst Fit Allocation Logic
//     for (int i = 0; i < p; i++) {
//         int maxFragmentation = INT_MIN; // Maximum leftover space
//         int block_no = -1;

//         // Find the block with the largest leftover space that can fit the process
//         for (int j = 0; j < n; j++) {
//             if (block[j] >= memoryreq[i]) { // Block can fit the process
//                 int fragmentation = block[j] - memoryreq[i];
//                 if (fragmentation > maxFragmentation) {
//                     maxFragmentation = fragmentation;
//                     block_no = j; // Store the index of the selected block
//                 }
//             }
//         }

//         // Allocate the selected block to the process
//         if (block_no != -1) {
//             assignblock[i] = block_no;       // Assign block number to the process
//             block[block_no] -= memoryreq[i]; // Reduce the size of the allocated block
//         }
//     }

//     // Output the allocation results
//     for (int i = 0; i < p; i++) {
//         if (assignblock[i] != -1) {
//             printf("Process %d with memory requirement %d allocated to block %d\n",
//                    i + 1, memoryreq[i], assignblock[i] + 1);
//         } else {
//             printf("Process %d with memory requirement %d could not be allocated\n",
//                    i + 1, memoryreq[i]);
//         }
//     }

//     return 0;
// }
