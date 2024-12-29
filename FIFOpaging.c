#include <stdio.h>
#include <stdbool.h>
#include <string.h>
struct PageTable
{
    int frame_no;
    bool valid;
};
bool isPagePresent(struct PageTable PT[], int page)
{
    if (PT[page].valid == 1)
    {
        return true;
    }
    return false;
}
void updatePageTable(struct PageTable PT[], int page, int fr_no, int status)
{
    PT[page].valid = status;
    if (status == 1)
        PT[page].frame_no = fr_no;
}
void printFrameContents(int frame[], int no_of_frames)
{
    for (int i = 0; i < no_of_frames; i++)
    {
        if (frame[i] != -1)
            printf("%d ", frame[i]);
    }
    printf("\n");
}
int main()
{
    int n, no_of_frames;
    printf("Enter the number of pages (page requests): ");
    scanf("%d", &n);
    int reference_string[n];
    printf("\nEnter the reference string(different page numbers):\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &reference_string[i]);
    }
    printf("Enter the no. of frames you want to give to the process:");
    scanf("%d", &no_of_frames);
    int frame[no_of_frames];
    memset(frame, -1, no_of_frames * sizeof(int));
    struct PageTable PT[50];
    for (int i = 0; i < 50; i++)
    {
        PT[i].valid = 0;
    }
    printf("\n***The contents inside the Frame array at different time: ***\n");
    int page_fault = 0, current = 0, flag = false;
    for (int i = 0; i < n; i++)
    {
        if (!isPagePresent(PT, reference_string[i]))
        {
            page_fault++;
            if (flag == false && current < no_of_frames)
            {
                frame[current] = reference_string[i];
                updatePageTable(PT, reference_string[i], current, 1);
                current += 1;
                if (current == no_of_frames)
                {
                    current = 0;
                    flag = true;
                }
            }
            else
            {
                updatePageTable(PT, frame[current], -1, 0);
                frame[current] = reference_string[i];
                updatePageTable(PT, reference_string[i], current, 1);
                current = (current + 1) % no_of_frames;
            }
            printFrameContents(frame, no_of_frames);
        }
    }
    printf("\nTotal No. of Page Faults = %d\n", page_fault);
    printf("\nPage Fault Ratio = %.2f\n", (float)page_fault / n);
    printf("\nPage Hit Ratio = %.2f", (float)(n - page_fault) / n);
    return 0;
}

// #include<stdio.h>
// #include<string.h>
// #include<stdbool.h>

// struct PageTable{
//     int frame_no;
//     bool valid;
// };

// //func to check if referenced/asked page is already present in frame[] or not
// bool isPagePresent(struct PageTable pt[], int page, int n)
// {
//     if(pt[page].valid == 1)
//         return true;

//     return false;
// }

// void updatePageTable(struct PageTable pt[], int page, int fr_no, int status)//page =frame[curr] or reference_string[i], fr_no =curr or -1, status 0 or 1
// {
// pt[page].valid = status;
// //if(status == 1)
//     pt[page].frame_no = fr_no;
// }

// void printFrameContent(int frame[], int no_of_frames)
// {
//     for(int i=0; i<no_of_frames; i++)
//     {
//         printf("%d",frame[i]);
//         printf("\n");
//     }
//     printf("\n");
// }

// int main()
// {
//     int n, no_of_frames, page_fault=0, curr =0;
//     bool flag = false;

//     printf("Enter no of pages: ");          //no of request
//     scanf("%d", &n);

//     int reference_string[n];                                    //create reference string array
//     printf("Enter the reference string(different page nos):\n");
//     for(int i=0; i<n; i++)
//     {
//         scanf("%d", &reference_string[i]);
//     }

//     printf("Enter no of frames you want to give to process: ");
//     scanf("%d", &no_of_frames);

//     int frame[no_of_frames];        //create frame array to store pages at differnet points of times
//     memset(frame, -1, no_of_frames *sizeof(int));

//     struct PageTable pt[50];
//     for(int i=0; i<50; i++)
//     {
//         pt[i].valid =0;
//     }

//     printf("**** content inside frame array at different time *** \n");

//     for(int i=0; i<n; i++)
//     {
//         //search ith page in all allocated frames
//         if(!(isPagePresent(pt, reference_string[i], n)))
//         {
//             page_fault++;
//             if(flag == false && curr < no_of_frames)
//             {
//                 frame[curr] = reference_string[i];

//                 printFrameContent(frame, no_of_frames);
//                 updatePageTable(pt, reference_string[i], curr, 1);

//                 curr = curr +1;
//                 if(curr == no_of_frames)
//                 {
//                     curr =0;
//                     flag = true;
//                 }
//             }
//             else
//             {       //frames are full, Apply FIFO
//                 //find fifo page to replace
//                 //page pointed by curr head is fifo page mark page as invalid in page table
//                 //set invalid frame no as -1 or anything
//                 updatePageTable(pt, frame[curr], -1, 0);
//                 frame[curr] = reference_string[i];

//                 printFrameContent(frame, no_of_frames);
//                 updatePageTable(pt,reference_string[i],curr,1);

//                 curr = ( curr + 1)% no_of_frames;
//                 }

//         }   //end outer if
//     }   //end for

//     printf("Total No. of Page Faults = %d\n",page_fault);
//     printf("Page Fault ratio = %.2f\n",(float)page_fault/n);
//     printf("Page Hit Ratio = %.2f\n",(float)(n- page_fault)/n);
//  return 0;

// }
