#include <stdio.h>
#include <string.h>
#define MAX_DISK_SIZE 1000      // Define maximum disk size
#define MAX_BLOCKS_PER_FILE 100 // Maximum blocks a file can take
struct File
{
    char name[20];                   // File name
    int indexBlock;                  // Index block (points to the index block for file's data)
    int length;                      // Length of the file in terms of blocks
    int blocks[MAX_BLOCKS_PER_FILE]; // Data blocks indexed by the index block
};
struct DiskBlock
{
    int occupied; // 0 means free, 1 means occupied
    int data;     // Data field (not used for indexing but could hold data in a real system)
};
struct Disk
{
    struct DiskBlock blocks[MAX_DISK_SIZE]; // Array of blocks in the disk
};
int allocateFile(struct Disk *disk, struct File *file)
{
    int requiredBlocks = file->length;
    int allocatedBlocks = 0;
    int currentBlock = -1;
    int indexBlockAllocated = 0;
    for (int i = 0; i < MAX_DISK_SIZE; i++)
    {
        if (disk->blocks[i].occupied == 0)
        { // Free block found
            if (allocatedBlocks == 0)
            {
                file->indexBlock = i;         // First free block becomes the index block
                disk->blocks[i].occupied = 1; // Mark the index block as occupied
                indexBlockAllocated = 1;
                allocatedBlocks++;
            }
            else
            {
                file->blocks[allocatedBlocks - 1] = i; // Store data blocks in file's blocks
                disk->blocks[i].occupied = 1;          // Mark block as occupied
                allocatedBlocks++;
            }
            if (allocatedBlocks == requiredBlocks + 1)
            {
                break;
            }
        }
    }
    if (allocatedBlocks < requiredBlocks + 1 || !indexBlockAllocated)
    {
        printf("Not enough free blocks available for file '%s'. Allocation failed.\n", file->name);
        return 0;
    }
    return 1; // Allocation successful
}
void searchFile(struct Disk *disk, struct File *files, int numFiles, const char *searchName)
{
    int found = 0;
    for (int i = 0; i < numFiles; i++)
    {
        if (strcmp(files[i].name, searchName) == 0)
        {
            printf("File Name: %s\n", files[i].name);
            printf("Index Block: %d\n", files[i].indexBlock);
            printf("File Length: %d\n", files[i].length);
            printf("Data Blocks: ");
            for (int j = 0; j < files[i].length; j++)
            {
                printf("%d ", files[i].blocks[j]);
            }
            printf("\n");
            found = 1;
            break;
        }
    }
    if (!found)
        printf("File does not exist\n");
}
int main()
{
    struct Disk disk;
    for (int i = 0; i < MAX_DISK_SIZE; i++)
    {
        disk.blocks[i].occupied = 0; // Set all blocks to free
        disk.blocks[i].data = 0;     // Empty data (not used in this basic implementation)
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
        printf("Length of file (in terms of blocks): ");
        scanf("%d", &files[i].length);
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
    searchFile(&disk, files, numFiles, searchName);
}