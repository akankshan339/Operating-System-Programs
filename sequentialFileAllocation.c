#include <stdio.h>
#include <string.h>
#define MAX_DISK_SIZE 1000
struct File
{
    char name[20];
    int startBlock;
    int length;
    int allocatedBlocks[MAX_DISK_SIZE];
};
struct Disk
{
    int blocks[MAX_DISK_SIZE];
};
int allocateFile(struct Disk *disk, struct File *file)
{
    memset(file->allocatedBlocks, -1, sizeof(file->allocatedBlocks));
    int start = file->startBlock;
    int length = file->length;
    int k = 0;
    for (int i = start; i < start + length; i++)
    {
        if (disk->blocks[i] == 1 || i >= MAX_DISK_SIZE)
        {
            memset(file->allocatedBlocks, -1, sizeof(file->allocatedBlocks));
            return 0; // Allocation failed
        }
        file->allocatedBlocks[k++] = i;
    }
    for (int i = start; i < start + length; i++)
    {
        disk->blocks[i] = 1;
    }
    return 1;
}
int main()
{
    struct Disk disk;
    memset(disk.blocks, 0, sizeof(disk.blocks)); // Initialize all disk blocks as free
    int numFiles;
    printf("Enter the number of files to store: ");
    scanf("%d", &numFiles);
    struct File files[numFiles];
    printf("\nEnter details for Files as Name, staring block (0 to %d), size of file\n", MAX_DISK_SIZE - 1);
    for (int i = 0; i < numFiles; i++)
    {
        printf("File %d: ", i + 1);
        scanf("%s", files[i].name);
        scanf("%d", &files[i].startBlock);
        scanf("%d", &files[i].length);
        // Attempt to allocate the file
        if (!allocateFile(&disk, &files[i]))
        {
            printf("Failed to allocate file '%s'. Not enough contiguous space or invalid block range.\n", files[i].name);
        }
    }
    printf("\nEnter the file name to be searched : ");
    char searchName[20];
    scanf("%s", searchName);
    int it = 0;
    for (it = 0; it < numFiles; it++)
    {
        if (strcmp(files[it].name, searchName) == 0)
        {
            printf("File Name : %s\n", files[it].name);
            printf("File Name : %d\n", files[it].startBlock);
            printf("File Name : %d\n", files[it].length);
            printf("Blocks Occupied : ");
            int k = 0;
            while (files[it].allocatedBlocks[k] != -1)
            {
                printf("%d ", files[it].allocatedBlocks[k]);
                k++;
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

// #include <stdio.h>
// #include <string.h>
// #define MAX_DISK_SIZE 50 // define maximum disk size

// // structure to represent file
// struct File
// {
//     char filename[10];
//     int startblock;
//     int filelen;
// };

// // structure to represent disk
// struct Disk
// {
//     int blocks[MAX_DISK_SIZE]; // binary array representing disk block(0 means free and 1 means occupied)
// };

// int alllocateFile(struct Disk *disk, struct File *file)
// {
//     int start = file->startblock;
//     int len = file->filelen;

//     // check if the requested block are free
//     for (int i = start; i < start + len; i++)
//     {
//         if (disk->blocks[i] == 1 || i >= MAX_DISK_SIZE)
//             return 0; // Allocation failed

//         else
//         {
//             disk->blocks[i] = 1; // mark block as occupied
//             return 0;
//         }
//     }
// }

// int main()
// {
//     struct Disk disk;
//     memset(disk.blocks, 0, sizeof(disk.blocks)); // initilize disc blocks as free

//     int nfiles;
//     printf("Enter no of files : ");
//     scanf("%d", &nfiles);

//     struct File files[nfiles];
//     for (int i = 0; i < nfiles; i++)
//     {
//         printf("Enter File Details: ");
//         printf("Enter File Name: ");
//         //scanf("%s", files[i].filename);
//         //fgets(files[i].filename);
//         fgets(files[i].filename, sizeof(files[i].filename), stdin);
//         printf("Enter staring block (0 to %d):", MAX_DISK_SIZE - 1);
//         scanf("%d", files[i].startblock);

//          //consumes all characters in the input buffer until it finds a newline.
//          //This ensures that the next scanf works as expected.

//         while (getchar() != '\n');
//         printf("Enter length of file: ");
//         scanf("%d", files[i].filelen);

//         // Attempt to allocate file
//         if (alllocateFile(&disk, &files[i]))
//             printf("File %s allocated successfully ! \n", files[i].filename);
//         else
//             printf("Failed to allocate file %s Not enough continguous space or invalid range\n", files[i].filename);
//     }

//     // Display allocation status of disk
//     printf("Disk Allocation Status:\n");
//     for (int i = 0; i < MAX_DISK_SIZE; i++)
//     {
//         printf("%d", disk.blocks[i]);
//         if ((i + 1) % 10 == 0)
//             printf("\n");
//     }
//     return 0;
// }

// #include <stdio.h>
// #include <string.h>
// #define MAX_DISK_SIZE 50 // define maximum disk size

// // structure to represent file
// struct File
// {
//     char filename[10];
//     int startblock;
//     int filelen;
// };

// // structure to represent disk
// struct Disk
// {
//     int blocks[MAX_DISK_SIZE]; // binary array representing disk block (0 means free and 1 means occupied)
// };

// int allocateFile(struct Disk *disk, struct File *file)
// {
//     int start = file->startblock;
//     int len = file->filelen;

//     // Check if requested blocks are free and within bounds
//     if (start < 0 || start + len > MAX_DISK_SIZE)
//         return 0;

//     for (int i = start; i < start + len; i++)
//     {
//         if (disk->blocks[i] == 1) // Block is already occupied
//             return 0;
//     }

//     // Mark blocks as occupied
//     for (int i = start; i < start + len; i++)
//     {
//         disk->blocks[i] = 1;
//     }
//     return 1; // Allocation successful
// }

// int main()
// {
//     struct Disk disk;
//     memset(disk.blocks, 0, sizeof(disk.blocks)); // Initialize disk blocks as free

//     int nfiles;
//     printf("Enter number of files: ");
//     scanf("%d", &nfiles);
//   //  getchar(); // Consume the leftover newline character

//     struct File files[nfiles];
//     for (int i = 0; i < nfiles; i++)
//     {
//         printf("Enter File Details:\n");
//         printf("Enter File Name: ");
//         fgets(files[i].filename, sizeof(files[i].filename), stdin);

//         // Remove newline character from filename if present
//         size_t len = strlen(files[i].filename);
//         if (len > 0 && files[i].filename[len - 1] == '\n')
//             files[i].filename[len - 1] = '\0';

//         printf("Enter starting block (0 to %d): ", MAX_DISK_SIZE - 1);
//         scanf("%d", &files[i].startblock);
//         printf("Enter length of file: ");
//         scanf("%d", &files[i].filelen);
//         getchar(); // Consume leftover newline character

//         // Attempt to allocate file
//         if (allocateFile(&disk, &files[i]))
//             printf("File %s allocated successfully!\n", files[i].filename);
//         else
//             printf("Failed to allocate file %s. Not enough contiguous space or invalid range\n", files[i].filename);
//     }

//     // Display allocation status of disk
//     printf("Disk Allocation Status:\n");
//     for (int i = 0; i < MAX_DISK_SIZE; i++)
//     {
//         printf("%d", disk.blocks[i]);
//         if ((i + 1) % 10 == 0)  //after 10 length , can come to next line
//             printf("\n");
//     }

//     return 0;
// }
