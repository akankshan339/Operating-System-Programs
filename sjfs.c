#include <stdio.h>
// #include<stdlib.h>
#include <stdbool.h>
#include <limits.h>
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

int findMax(int a, int b)
{
    return (a > b) ? a : b;
}

int findMin(int a, int b)
{
    return (a < b) ? a : b;
}
int main()
{
    int n;
    printf("Entre the no of Process:\n");
    scanf("%d", &n);

    struct Process p[n];
    printf("Enter the Arrival Time and Burst Time of Processes:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &p[i].at, &p[i].bt);
        p[i].pid = i;
    }

    int completed = 0, currTime = 0, prev = 0;
    int sumtat = 0, sumwt = 0, sumrt = 0, total_idleTime = 0, lengthCycle = 0;
    bool is_Complete[4] = {false}, isFirstProcess = true;
    float cpu_Utilization, throughput;
    int ganttProcessOrder[n], ganttIndex = 0;

    // Initialize the array with 'false'  if is_Complete[n];
    // for (int i = 0; i < n; i++) {
    //     is_Complete[i] = false;
    // }

    while (completed != n)
    {
        int minidx = -1;
        int mini = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= currTime && is_Complete[i] == false)
            {
                if (p[i].bt < mini)
                {
                    mini = p[i].bt;
                    minidx = i;
                }

                if (p[i].bt == mini)
                {
                    if (p[i].at < p[minidx].at)
                    {
                        mini = p[i].bt;
                        minidx = i;
                    }
                }
            }
        }

        if (minidx == -1)
            currTime++;
        else
        {
            p[minidx].st = currTime;
            p[minidx].ct = p[minidx].st + p[minidx].bt;
            p[minidx].tat = p[minidx].ct - p[minidx].at;
            p[minidx].wt = p[minidx].tat - p[minidx].bt;
            p[minidx].rt = p[minidx].wt;
            // p[minidx].rt = p[minidx].st - p[minidx].at;

            sumtat += p[minidx].tat;
            sumwt += p[minidx].wt;
            sumrt += p[minidx].rt;
            total_idleTime += (isFirstProcess == true) ? 0 : p[minidx].st - prev;

            ganttProcessOrder[ganttIndex] = p[minidx].pid;
            // ganttStartTimes[ganttIndex] = p[minidx].st;
            // ganttEndTimes[ganttIndex] = p[minidx].ct;
            ganttIndex++;

            completed++;
            currTime = p[minidx].ct;
            prev = currTime;
            is_Complete[minidx] = true;
            isFirstProcess = false;
        }
    } // closing of while

    int max_completionTime = INT_MIN;
    int min_ArrivalTime = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        max_completionTime = findMax(max_completionTime, p[i].ct);
        min_ArrivalTime = findMin(min_ArrivalTime, p[i].at);
    }

    lengthCycle = max_completionTime - min_ArrivalTime;
    cpu_Utilization = (float)(lengthCycle - total_idleTime) * 100 / lengthCycle;
    throughput = (float)n / lengthCycle;

    printf("GANTT CHART : ");
    for (int i = 0; i < ganttIndex; i++)
    {
        printf("P%d ", ganttProcessOrder[i]);
    }
    printf("\n");

    // // Printing process execution order
    //     for (int i = 0; i < ganttIndex; i++) {
    //         printf("|  P%d  ", ganttProcessOrder[i]);
    //     }
    //     printf("|\n");

    // Printing the start and end times of each process
    // printf("%d", ganttStartTimes[0]);
    // for (int i = 0; i < ganttIndex; i++) {
    //     printf("      %d", ganttEndTimes[i]);
    // }
    // printf("\n");

    // printf("Total Turn Around Time = %d\n",sumtat);
    // printf("Total Waiting Time = %d\n",sumwt);
    // printf("Total Response Time = %d\n",sumrt);
    // printf("Total Idle Time = %d\n",total_idleTime);
    // printf("Length Cycle = %d\n",lengthCycle);

    printf("Average Turn Around Time = %.2f\n", (float)sumtat / n);
    printf("Average Waiting Time = %.2f\n", (float)sumwt / n);
    printf("Average Response Time = %.2f\n", (float)sumrt / n);

    printf("Pid\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\n", p[i].pid, p[i].at, p[i].bt, p[i].st, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("CPU Utilization = %.2f\n", cpu_Utilization);
    printf("Throughput = %.2f", throughput);

    return 0;
}