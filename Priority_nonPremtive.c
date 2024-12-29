#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

struct Process
{
    int pid;
    int priority;
    int at;
    int bt;
    int st;
    int ct;
    int rt;
    int tat;
    int wt;
};

int findmax(int a, int b)
{
    return a > b ? a : b;
}

int findmin(int a, int b)
{
    return a < b ? a : b;
}

int main()
{
    int completed = 0, currtime = 0;
    int total_idle_time = 0, prev = 0, lengthCycle = 0;
    float sum_tat = 0, sum_wt = 0, sum_rt = 0;
    int max_completion_time, min_arrival_time;
    float cpu_utilization = 0.0;
    int ganttProcessOrder[10], ganttIndex = 0;
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    bool is_completed[n];
    for (int i = 0; i < n; i++)
        is_completed[i] = false;

    bool isFirstProcess = true;

    for (int i = 0; i < n; i++)
    {
        printf("\nEnter Process %d Arrival Time, Burst Time, and Priority: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
        p[i].pid = i + 1;
    }

    while (completed != n)
    {
        int max_idx = -1;
        int maximum = -1;

        // Find the process with the highest priority that has arrived
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= currtime && !is_completed[i])
            {
                if (p[i].priority > maximum)
                {
                    maximum = p[i].priority;
                    max_idx = i;
                }

                if (p[i].priority == maximum)
                {
                    if (p[i].at < p[max_idx].at)
                    {
                        max_idx = i;
                    }
                }
            }
        }

        if (max_idx == -1)
        {
            currtime++; // If no process is ready, increment current time
        }
        else
        {
            // If a process is found, schedule it
            if (isFirstProcess)
            {
                p[max_idx].st = p[max_idx].at; // First process starts at its arrival time
                isFirstProcess = false;
            }
            else
            {
                p[max_idx].st = findmax(currtime, p[max_idx].at); // Start time is either current time or after arrival
                total_idle_time += p[max_idx].st - currtime;      // Track idle time if CPU was idle
            }

            p[max_idx].ct = p[max_idx].st + p[max_idx].bt;  // Completion time
            p[max_idx].tat = p[max_idx].ct - p[max_idx].at; // Turnaround time
            p[max_idx].wt = p[max_idx].tat - p[max_idx].bt; // Waiting time
            p[max_idx].rt = p[max_idx].st - p[max_idx].at;  // Response time

            // Update Gantt chart
            ganttProcessOrder[ganttIndex++] = p[max_idx].pid;

            sum_tat += p[max_idx].tat;
            sum_wt += p[max_idx].wt;
            sum_rt += p[max_idx].rt;

            completed++;
            currtime = p[max_idx].ct;
            prev = currtime;

            is_completed[max_idx] = true;

            // Debugging information
            printf("\nProcess %d scheduled:\n", p[max_idx].pid);
            printf("Start Time: %d, Completion Time: %d, Turnaround Time: %d, Waiting Time: %d\n",
                   p[max_idx].st, p[max_idx].ct, p[max_idx].tat, p[max_idx].wt);
        }
    }

    // Calculate Length of Process completion cycle
    max_completion_time = INT_MIN;
    min_arrival_time = INT_MAX;
    int total_burst_time = 0;

    for (int i = 0; i < n; i++)
    {
        max_completion_time = findmax(max_completion_time, p[i].ct);
        min_arrival_time = findmin(min_arrival_time, p[i].at);
        total_burst_time += p[i].bt;
    }

    lengthCycle = max_completion_time - min_arrival_time;
    cpu_utilization = ((float)total_burst_time / lengthCycle) * 100;

    // Print Gantt Chart
    printf("\nGANTT CHART: ");
    for (int i = 0; i < ganttIndex; i++)
    {
        printf("P%d ", ganttProcessOrder[i]);
    }
    printf("\n");

    printf("\nPID\tAT\tBT\tPr\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].priority, p[i].st, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nAverage Turn Around Time: %.2f", sum_tat / n);
    printf("\nAverage Waiting Time: %.2f", sum_wt / n);
    printf("\nAverage Response Time: %.2f", sum_rt / n);
    printf("\nThroughput: %.2f", (float)n / lengthCycle);
    printf("\nCPU Utilization = %.2f%%", cpu_utilization);

    return 0;
}

// #include<stdio.h>
// #include<stdlib.h>
// #include<limits.h>
// #include<stdbool.h>

// struct Process {
//     int pid;
//     int priority;
//     int at;
//     int bt;
//     int st;
//     int ct;
//     int rt;
//     int tat;
//     int wt;
// };

// int findmax(int a, int b)
// {
//  return a>b?a:b;
// }
// int findmin(int a, int b)
// {
//  return a<b?a:b;
// }

// int main()
// {
//     int completed=0, currtime =0;
//     int total_idle_time =0, prev =0, lengthCycle =0;
//     float sum_tat =0, sum_wt =0, sum_rt =0;
//      int max_completion_time, min_arrival_time, cpu_utilization =0;
//     int n;
//     printf("Enter no of processes:\n");
//     scanf("%d", &n);
//     struct Process p[n];
//     bool is_completed[5] = {false}, isFirstProcess = true;
//      for (int i = 0; i < n; i++)
//     {
//         printf("\nEnter Process %d Arrival Time ,  Burst Time and Priority: ", i+1);
//         scanf("%d%d%d", &p[i].at, &p[i].bt, &p[i].priority);
//         p[i].pid = i+1;
//     }
//     while(completed != n)
//     {
// //find the process with min burst time in ready queue at curr time
// int max_idx =-1;
// int maximum =-1;
// for(int i=0; i<n; i++)
// {
//     if(p[i].at <= currtime && is_completed[i] == false)
//     {
//         if(p[i].priority > maximum)
//         {
//             maximum = p[i].priority;
//             max_idx = i;
//         }

//          if(p[i].priority == maximum)
//         {
//             if(p[i].at < p[max_idx].at)
//             {
//             maximum = p[i].priority;
//             max_idx = i;
//             }
//         }
//     }
// }
// if(max_idx == -1)
// {
//     currtime++;

// }
// else
// {
// p[max_idx].st = currtime;
// p[max_idx].ct = p[max_idx].st + p[max_idx].bt;
// p[max_idx].tat = p[max_idx].ct - p[max_idx].at;
// p[max_idx].wt = p[max_idx].tat - p[max_idx].bt;
// p[max_idx].rt = p[max_idx].st - p[max_idx].at;
// total_idle_time += (isFirstProcess == true)? 0 : (p[max_idx].st - prev);

// sum_tat += p[max_idx].tat;
// sum_wt += p[max_idx].wt;
// sum_rt += p[max_idx].rt;

// completed++;
// currtime = p[max_idx].ct;
// prev= currtime;

// is_completed[max_idx]=true;
// isFirstProcess = false;
// }
// }

// ///Calculate Length of Process completion cycle
//  max_completion_time = INT_MIN;
//  min_arrival_time = INT_MAX;
//  for(int i=0;i<n;i++)
//  {
//  max_completion_time = findmax(max_completion_time,p[i].ct);
//  min_arrival_time = findmin(min_arrival_time,p[i].at);
//  }
//  lengthCycle = max_completion_time - min_arrival_time;
//  cpu_utilization = (float)(lengthCycle - total_idle_time) *100/ lengthCycle;

//   printf("\nPID\tAT\tBT\tPr\tST\tCT\tTAT\t\tWT\t\tRT\n");
//     for (int i = 0; i < n; i++) {
//         printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\n",p[i].pid, p[i].at, p[i].bt, p[i].priority, p[i].st, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
//     }
//  printf("\nAverage Turn Around Time%.2f",(float)sum_tat/n);
//  printf("\nAverage Waiting Time %.2f",(float)sum_wt/n);
//  printf("\nAverage Responce Time %.2f",(float)sum_rt/n);
//  printf("\nThroughput %.2f",(float)(n/lengthCycle));
//  printf("\nCPU Utilization = %.2f",cpu_utilization);
// return 0;
// }