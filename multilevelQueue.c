#include <stdio.h>
#include <stdlib.h>
struct Process
{
    int pid;   // Process ID
    int at;    // Arrival Time
    int bt;    // Burst Time
    int ct;    // Completion Time
    float tat; // Turnaround Time
    float wt;  // Waiting Time
    int rt;    // Response Time
    int st;    // Start Time
};
int compare(const void *p1, const void *p2)
{
    int a = ((struct Process *)p1)->at;
    int b = ((struct Process *)p2)->at;
    return (a < b) ? -1 : 1;
}
int main()
{
    int n, sys_count;
    float swt = 0, stat = 0;
    float cu = 0, throughput = 0;
    float awt = 0, atat = 0;
    int sbt = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    // Input burst time and arrival time for each process
    for (int i = 0; i < n; i++)
    {
        printf("For Process %d: ", i + 1);
        p[i].pid = i + 1;
        printf("Enter the value of AT and BT: ");
        scanf("%d %d", &p[i].at, &p[i].bt);
    }
    printf("Enter the number of system processes: ");
    scanf("%d", &sys_count);
    // Input the PIDs of the system processes
    int sys_pids[sys_count];
    printf("Enter the PIDs of system processes: ");
    for (int i = 0; i < sys_count; i++)
    {
        scanf("%d", &sys_pids[i]);
    }
    struct Process system_queue[sys_count], user_queue[n - sys_count];
    int sys_index = 0, user_index = 0;
    for (int i = 0; i < n; i++)
    {
        int is_system = 0;
        for (int j = 0; j < sys_count; j++)
        {
            if (p[i].pid == sys_pids[j])
            {
                is_system = 1;
                break;
            }
        }
        if (is_system)
        {
            system_queue[sys_index++] = p[i]; // System process
        }
        else
        {
            user_queue[user_index++] = p[i]; // User process
        }
    }

    qsort(system_queue, sys_index, sizeof(struct Process), compare);
    qsort(user_queue, user_index, sizeof(struct Process), compare);
    int current_time = 0;
    // Function to calculate times for FCFS
    void calculate_times(struct Process q[], int count, int *current_time)
    {
        for (int i = 0; i < count; i++)
        {
            if (i == 0)
            {
                q[i].st = (*current_time > q[i].at) ? *current_time : q[i].at;
                q[i].ct = q[i].st + q[i].bt;
            }
            else
            {
                q[i].st = (q[i - 1].ct > q[i].at) ? q[i - 1].ct : q[i].at;
                q[i].ct = q[i].st + q[i].bt;
            }
            q[i].tat = q[i].ct - q[i].at;
            q[i].wt = q[i].tat - q[i].bt;
            q[i].rt = q[i].st - q[i].at;
            sbt += q[i].bt;
            swt += q[i].wt;
            stat += q[i].tat;
            *current_time = q[i].ct; // Update the current time after process execution
        }
    }
    calculate_times(system_queue, sys_index, &current_time);
    calculate_times(user_queue, user_index, &current_time);
    // Print Gantt Chart
    printf("\nGantt Chart: ");
    for (int i = 0; i < sys_index; i++)
    {
        printf("P%d ", system_queue[i].pid);
    }
    for (int i = 0; i < user_index; i++)
    {
        printf("P%d ", user_queue[i].pid);
    }
    printf("\n");
    awt = swt / n;
    atat = stat / n;
    // CPU utilization and throughput calculation
    float max_ct = 0;
    for (int i = 0; i < sys_index; i++)
    {
        if (system_queue[i].ct > max_ct)
            max_ct = system_queue[i].ct;
    }
    for (int i = 0; i < user_index; i++)
    {
        if (user_queue[i].ct > max_ct)
            max_ct = user_queue[i].ct;
    }
    cu = (sbt / max_ct) * 100;
    throughput = n / max_ct;
    // Printing results
    printf("\nPID\tAT\tBT\tST\tCT\tTAT\t\tWT\t\tRT\n");
    for (int i = 0; i < sys_index; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%f\t%f\t%d\n", system_queue[i].pid, system_queue[i].at,
               system_queue[i].bt,
               system_queue[i].st, system_queue[i].ct, system_queue[i].tat, system_queue[i].wt,
               system_queue[i].rt);
    }
    for (int i = 0; i < user_index; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%f\t%f\t%d\n", user_queue[i].pid, user_queue[i].at,
               user_queue[i].bt, user_queue[i].st, user_queue[i].ct, user_queue[i].tat, user_queue[i].wt,
               user_queue[i].rt);
    }
    printf("\nSum of Turnaround Time: %f\nAverage Turnaround Time: %f\n", stat, atat);
    printf("Sum of Waiting Time: %f\nAverage Waiting Time: %f\nCPU Utilization:%f%%\nThroughput: %f\n", swt, awt, cu, throughput);
    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>

// struct Process {
//     int pid;       // Process ID
//     int at;        // Arrival Time
//     int bt;        // Burst Time
//     int ct;        // Completion Time
//     float tat;     // Turnaround Time
//     float wt;      // Waiting Time
//     int rt;        // Response Time
//     int st;        // Start Time
// };

// // Function to compare processes by arrival time for sorting
// int compare(const void *p1, const void *p2) {
//     int a = ((struct Process *)p1)->at;
//     int b = ((struct Process *)p2)->at;
//     return (a < b) ? -1 : 1;
// }

// int main() {
//     int n, sys_count;
//     float swt = 0, stat = 0;
//     float cu = 0, throughput = 0;
//     float awt = 0, atat = 0;
//     int sbt = 0;

//     // Input the number of processes
//     printf("Enter the number of processes: ");
//     scanf("%d", &n);
//     struct Process p[n];

//     // Input burst time and arrival time for each process
//     for (int i = 0; i < n; i++) {
//         printf("For Process %d: ", i + 1);
//         p[i].pid = i + 1;
//         printf("Enter the value of AT and BT: ");
//         scanf("%d %d", &p[i].at, &p[i].bt);
//     }

//     // Input the number of system processes
//     printf("Enter the number of system processes: ");
//     scanf("%d", &sys_count);

//     // Input the PIDs of the system processes
//     int sys_pids[sys_count];
//     printf("Enter the PIDs of system processes: ");
//     for (int i = 0; i < sys_count; i++) {
//         scanf("%d", &sys_pids[i]);
//     }

//     // Divide processes into system and user processes
//     struct Process system_queue[sys_count], user_queue[n - sys_count];
//     int sys_index = 0, user_index = 0;

//     for (int i = 0; i < n; i++) {
//         int is_system = 0;
//         for (int j = 0; j < sys_count; j++) {
//             if (p[i].pid == sys_pids[j]) {
//                 is_system = 1;
//                 break;
//             }
//         }
//         if (is_system) {
//             system_queue[sys_index++] = p[i]; // System process
//         } else {
//             user_queue[user_index++] = p[i];  // User process
//         }
//     }

//     // Sort both queues by arrival time
//     qsort(system_queue, sys_index, sizeof(struct Process), compare);
//     qsort(user_queue, user_index, sizeof(struct Process), compare);

//      int current_time = 0;

//     // Function to calculate times for FCFS
//     void calculate_times(struct Process q[], int count, int *current_time) {
//         for (int i = 0; i < count; i++) {
//             if (i == 0) {
//                 q[i].st = (*current_time > q[i].at) ? *current_time : q[i].at;
//                 q[i].ct = q[i].st + q[i].bt;
//             } else {
//                 q[i].st = (q[i - 1].ct > q[i].at) ? q[i - 1].ct : q[i].at;
//                 q[i].ct = q[i].st + q[i].bt;
//             }
//             q[i].tat = q[i].ct - q[i].at;
//             q[i].wt = q[i].tat - q[i].bt;
//             q[i].rt = q[i].st - q[i].at;

//             sbt += q[i].bt;
//             swt += q[i].wt;
//             stat += q[i].tat;

//             *current_time = q[i].ct;  // Update the current time after process execution
//         }
//     }

//     // int current_time = 0;

//     // Calculate times for system processes
//     calculate_times(system_queue, sys_index, &current_time);

//     // Calculate times for user processes
//     calculate_times(user_queue, user_index, &current_time);

//     // Print Gantt Chart
//     printf("\nGantt Chart: ");
//     for (int i = 0; i < sys_index; i++) {
//         printf("P%d ", system_queue[i].pid);
//     }
//     for (int i = 0; i < user_index; i++) {
//         printf("P%d ", user_queue[i].pid);
//     }
//     printf("\n");

//     // Average waiting time and turnaround time
//     awt = swt / n;
//     atat = stat / n;

//     // CPU utilization and throughput calculation
//     float max_ct = 0;
//     for (int i = 0; i < sys_index; i++) {
//         if (system_queue[i].ct > max_ct)
//             max_ct = system_queue[i].ct;
//     }
//     for (int i = 0; i < user_index; i++) {
//         if (user_queue[i].ct > max_ct)
//             max_ct = user_queue[i].ct;
//     }

//     cu = (sbt / max_ct) * 100;
//     throughput = n / max_ct;

//     // Printing results
//     printf("\nPID\tAT\tBT\tST\tCT\tTAT\t\tWT\t\tRT\n");
//     for (int i = 0; i < sys_index; i++) {
//         printf("P%d\t%d\t%d\t%d\t%d\t%f\t%f\t%d\n", system_queue[i].pid, system_queue[i].at, system_queue[i].bt,
//                system_queue[i].st, system_queue[i].ct, system_queue[i].tat, system_queue[i].wt, system_queue[i].rt);
//     }
//     for (int i = 0; i < user_index; i++) {
//         printf("P%d\t%d\t%d\t%d\t%d\t%f\t%f\t%d\n", user_queue[i].pid, user_queue[i].at, user_queue[i].bt,
//                user_queue[i].st, user_queue[i].ct, user_queue[i].tat, user_queue[i].wt, user_queue[i].rt);
//     }

//     printf("\nSum of Turnaround Time: %f\nAverage Turnaround Time: %f\n", stat, atat);
//     printf("Sum of Waiting Time: %f\nAverage Waiting Time: %f\nCPU Utilization: %f%%\nThroughput: %f\n", swt, awt, cu, throughput);

//     return 0;
// }