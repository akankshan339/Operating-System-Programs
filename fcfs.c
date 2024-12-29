// n =6
// AT BT
// 3  3
// 2  4
// 1  7
// 0  1
// 4  2
// 2  2
#include <stdio.h>
// #include<unistd.h>
#include <stdlib.h>
struct Process
{
    int pid;
    int at;
    int bt;
    int st;
    int ct;
    int tat;
    int wt;
    int rt;
};

int comparatorAT(const void *a, const void *b)
{
    int x = ((struct Process *)a)->at;
    int y = ((struct Process *)b)->at;
    if (x < y)
        return -1;
    else if (x >= y) // sort
        return 1;
}

// int comparatorAT(const void *a, const void *b)
// {
//     const struct Process *p1 = (const struct Process*)a;
//     const struct Process *p2 = (const struct Process*)b;

//     if (p1->at < p2->at)
//         return -1;
//     else if (p1->at > p2->at)
//         return 1;
//     else
//     {
//         // Secondary sort based on PID to maintain input order
//         if (p1->pid < p2->pid)
//             return -1;
//         else if (p1->pid > p2->pid)
//             return 1;
//         else
//             return 0;
//     }
// }

int comparatorPid(const void *a, const void *b)
{
    int x = ((struct Process *)a)->pid;
    int y = ((struct Process *)b)->pid;
    if (x < y)
        return -1;
    else if (x > y)
        return 1;
    // else
    //     return 0;
}

int findMax(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}
int main()
{
    int n;
    printf("Enter no of Process :\n");
    scanf("%d", &n);
    struct Process p[n];
    int sumtat = 0, sumwt = 0, sumrt = 0, length_cycle = 0, total_idleTime = 0;
    float cpu_utilization, throughput;
    printf("Enter the Arrival Time and Burst Time:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &p[i].at);
        scanf("%d", &p[i].bt);
        p[i].pid = i;
    }

    qsort((void *)p, n, sizeof(struct Process), comparatorAT); // sort all arrays on basis of arival time

    // calculations
    for (int i = 0; i < n; i++)
    {
        p[i].st = (i == 0) ? p[i].at : findMax(p[i].at, p[i - 1].ct);
        p[i].ct = p[i].st + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        p[i].rt = p[i].wt;

        sumtat += p[i].tat;
        sumwt += p[i].wt;
        sumrt += p[i].rt;

        total_idleTime += (i == 0) ? 0 : p[i].st - p[i - 1].ct; // p[i].at
    }

    length_cycle = p[n - 1].ct - p[0].st;
    cpu_utilization = (float)(length_cycle - total_idleTime) * 100 / length_cycle;
    throughput = (float)n / length_cycle;

    printf("GANTT CHART : ");
    for (int i = 0; i < n; i++)
    {
        printf("P%d ", p[i].pid);
    }

    // arranging the table such that pid is sorted
    qsort((void *)p, n, sizeof(struct Process), comparatorPid);

    printf("\nTable is :\n");
    printf("Pid\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].st, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    //  printf("Total Turn Around Time = %d\n", sumtat);
    //  printf("Total Waiting Time = %d\n", sumwt);
    //  printf("Total Response Time = %d\n", sumrt);
    printf("\nAverage Turn Around time= %.2f ", (float)sumtat / n);
    printf("\nAverage Waiting Time= %.2f ", (float)sumwt / n);
    printf("\nAverage Response Time= %.2f ", (float)sumrt / n);
    printf("\nCPU Utilization = %.2f\n", cpu_utilization);
    printf("Throughput = %.2f\n", throughput);

    return 0;
}