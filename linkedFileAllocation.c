#include <stdio.h>
#include <string.h>
#define MAX_DISK_SIZE 1000 // Define maximum disk size
struct File
{
    char name[20];
    int startBlock;
    int length;
};
struct DiskBlock
{
    int occupied;  // 0 means free, 1 means occupied
    int nextBlock; // Stores the index of the next block in the linked list
};
struct Disk
{
    struct DiskBlock blocks[MAX_DISK_SIZE];
};
// Allocate file blocks using linked-list allocation
int allocateFile(struct Disk *disk, struct File *file)
{
    int requiredBlocks = file->length;
    int allocatedBlocks = 0;
    int currentBlock = file->startBlock;
    int previousBlock = -1;
    if (file->startBlock >= MAX_DISK_SIZE || file->startBlock < 0)
    {
        printf("Invalid start block. Allocation failed.\n");
        return 0;
    }
    while (allocatedBlocks < requiredBlocks)
    {
        if (currentBlock >= MAX_DISK_SIZE || disk->blocks[currentBlock].occupied == 1)
        {
            return 0; // Allocation failed
        }
        disk->blocks[currentBlock].occupied = 1; // Mark block as occupied
        if (previousBlock != -1)
        {
            disk->blocks[previousBlock].nextBlock = currentBlock;
        }
        previousBlock = currentBlock;
        allocatedBlocks++;
        int foundNext = 0;
        for (int i = 0; i < MAX_DISK_SIZE; i++)
        {
            if (disk->blocks[i].occupied == 0)
            {
                currentBlock = i;
                foundNext = 1;
                break;
            }
        }
        if (!foundNext && allocatedBlocks < requiredBlocks)
        {
            return 0; // No more free blocks and still need more blocks
        }
    }
    disk->blocks[previousBlock].nextBlock = -1; // End of the linked list
    return 1;                                   // Allocation successful
}
int main()
{
    struct Disk disk;
    for (int i = 0; i < MAX_DISK_SIZE; i++)
    {
        disk.blocks[i].occupied = 0;
        disk.blocks[i].nextBlock = -1; // Initialize all blocks as free and without a next block
    }
    int numFiles;
    printf("Enter the number of files to store: ");
    scanf("%d", &numFiles);
    struct File files[numFiles];
    for (int i = 0; i < numFiles; i++)
    {
        printf("\nEnter details for File %d:\n", i + 1);
        printf("File name: ");
        scanf("%s", files[i].name);
        printf("Starting block (0 to %d): ", MAX_DISK_SIZE - 1);
        scanf("%d", &files[i].startBlock);
        printf("Length of file: ");
        scanf("%d", &files[i].length);
        // Attempt to allocate the file
        if (allocateFile(&disk, &files[i]))
        {
            printf("File '%s' allocated successfully!\n", files[i].name);
        }
        else
        {
            printf("Failed to allocate file '%s'. Not enough free blocks or invalid block range.\n",
                   files[i].name);
        }
    }
    printf("\nEnter the file name to be searched: ");
    char searchName[20];
    scanf("%s", searchName);
    int it = 0;
    for (it = 0; it < numFiles; it++)
    {
        if (strcmp(files[it].name, searchName) == 0)
        {
            printf("File Name: %s\n", files[it].name);
            printf("Start Block: %d\n", files[it].startBlock);
            printf("File Length: %d\n", files[it].length);
            printf("Blocks Occupied: ");
            int k = files[it].startBlock;
            while (k != -1)
            {
                printf("%d ", k);
                k = disk.blocks[k].nextBlock;
            }
            printf("\n");
            break;
        }
    }
    if (it == numFiles)
    {
        printf("File does not exist\n");
    }
    return 0;
}