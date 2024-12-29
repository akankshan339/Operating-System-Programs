#include<stdio.h>
#include<stdlib.h>

struct Process {
    int pid;
    float at;
    float bt;
    float st;
    float ct;
    float rt;
    float tat;
    float wt;
    float isSysProcess;
};
int main()
{
    int n;
    printf("Enter no of processes:\n");
    scanf("%d", &n);
    struct Process p[n];
     for (int i = 0; i < n; i++)
    {
        printf("\nEnter Process %d Arrival Time and Burst Time: ", i);
        scanf("%f%f", &p[i].at, &p[i].bt);
        p[i].pid = i;
        p[i].isSysProcess= i;
    }
    
    
return 0;
}