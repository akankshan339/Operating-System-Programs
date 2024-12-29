// Preemptive Priority
#include <stdio.h>
#include <stdbool.h>
struct process_struct
{
    int at;
    int bt;
    int priority;
    int ct, wt, tat, rt, start_time;
} ps[100];
int main()
{
    int n;
    bool is_completed[100] = {false};
    int bt_remaining[100];
    int current_time = 0, completed = 0;
    int gantt_chart[1000], gc_index = 0; // Array to store Gantt chart (assuming max 1000 time units)

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    float sum_tat = 0, sum_wt = 0, sum_rt = 0;
    int i;
    // Input arrival time, burst time, and priority
    printf("\nEnter Process Arrival Time\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &ps[i].at);
    }
    printf("\nEnter Process Burst Time\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &ps[i].bt);
        bt_remaining[i] = ps[i].bt; // Initialize remaining burst time
    }
    printf("\nEnter Priority\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &ps[i].priority);
    }
    while (completed != n)
    {
        // Find the process with the highest priority that has arrived
        int max_index = -1;
        int maximum = -1;

        for (int i = 0; i < n; i++)
        {
            if (ps[i].at <= current_time && is_completed[i] == false)
            {
                if (ps[i].priority > maximum)
                {
                    maximum = ps[i].priority;
                    max_index = i;
                }
                if (ps[i].priority == maximum)
                {
                    if (ps[i].at < ps[max_index].at)
                    {
                        maximum = ps[i].priority;
                        max_index = i;
                    }
                }
            }
        }
        if (max_index == -1)
        {
            current_time++;
        }
        else
        {
            // If process starts for the first time, record start time
            if (bt_remaining[max_index] == ps[max_index].bt)
                ps[max_index].start_time = current_time;

            // Execute the process for one unit of time
            bt_remaining[max_index]--;
            gantt_chart[gc_index++] = max_index; // Store the process ID in Gantt chart
            current_time++;
            // If process is completed
            if (bt_remaining[max_index] == 0)
            {
                ps[max_index].ct = current_time;
                ps[max_index].tat = ps[max_index].ct - ps[max_index].at;
                ps[max_index].wt = ps[max_index].tat - ps[max_index].bt;
                ps[max_index].rt = ps[max_index].start_time - ps[max_index].at;
                sum_tat += ps[max_index].tat;
                sum_wt += ps[max_index].wt;
                sum_rt += ps[max_index].rt;
                completed++;
                is_completed[max_index] = true;
            }
        }
    }
    // Print completion times

    printf("\nCompletion times:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", ps[i].ct);
    }
    // Print averages
    printf("\nAverage Turn Around Time: %.2f", sum_tat / n);
    printf("\nAverage Waiting Time: %.2f", sum_wt / n);
    printf("\nAverage Response Time: %.2f", sum_rt / n);
    // Print Gantt Chart
    printf("\n\nGantt Chart:\n");
    for (int i = 0; i < gc_index; i++)
    {
        printf("| P%d ", gantt_chart[i] + 1); // +1 for 1-based process numbering
    }
    printf("|\n");
    return 0;
}