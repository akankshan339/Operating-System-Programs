#include <stdio.h>
#include <stdlib.h>

int main()
{
    int req, total_seek = 0;
    printf("Enter the no of disc requests: ");
    scanf("%d", &req);

    int discArr[req];
    printf("Enter total no of tracking nos: ");
    for (int i = 0; i < req; i++)
    {
        scanf("%d", &discArr[i]);
    }
    // int intial = discArr[0];
    int intial, curr;
    printf("Enter the initial seek pointer: ");
    scanf("%d", &intial);

    for (int i = 0; i < req; i++)
    {
        int diff = abs(discArr[i] - intial);
        intial = discArr[i];
        total_seek += diff;
    }
    printf("Total Seek Movement: %d", total_seek);
    // print seek sequence
    for (int i = 0; i < req; i++)
    {
        printf("%d", discArr[i]);
    }
    return 0;
}