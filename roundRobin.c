#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
struct process_struct
{
    int pid;
    int at;
    int bt;
    int ct, wt, tat, rt, start_time;
    int bt_remaining;
} ps[100];
int findmax(int a, int b)
{
    return a > b ? a : b;
}
int comparatorAT(const void *a, const void *b)
{
    int x = ((struct process_struct *)a)->at;
    int y = ((struct process_struct *)b)->at;
    return (x < y) ? -1 : 1;
}
int compare_pid(const void *a, const void *b)
{
    int x = ((struct process_struct *)a)->pid;
    int y = ((struct process_struct *)b)->pid;
    return (x < y) ? -1 : (x > y) ? 1: 0;
}
int main()
{
    int n, index;
    float cpu_utilization;
    bool visited[100] = {false}, is_first_process = true;
    int current_time = 0, max_completion_time;
    int completed = 0, tq, total_idle_time = 0, length_cycle;
    int queue[100], front = -1, rear = -1;
    float sum_tat = 0, sum_wt = 0, sum_rt = 0;
    int gantt_chart[1000], gc_index = 0; // Array to store Gantt chart
    printf("Enter total number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("\nEnter Process %d Arrival Time: ", i);
        scanf("%d", &ps[i].at);
        ps[i].pid = i;
    }
    for (int i = 0; i < n; i++)
    {
        printf("\nEnter Process %d Burst Time: ", i);
        scanf("%d", &ps[i].bt);
        ps[i].bt_remaining = ps[i].bt;
    }
    printf("\nEnter time quantum: ");
    scanf("%d", &tq);
    qsort(ps, n, sizeof(struct process_struct), comparatorAT);
    front = rear = 0;
    queue[rear] = 0;
    visited[0] = true;
    while (completed != n)
    {
        index = queue[front++];
        if (ps[index].bt_remaining == ps[index].bt)
        {
            ps[index].start_time = findmax(current_time, ps[index].at);
            total_idle_time += (is_first_process) ? 0 : ps[index].start_time - current_time;
            current_time = ps[index].start_time;
            is_first_process = false;
        }
        gantt_chart[gc_index++] = ps[index].pid; // Record process execution in Gantt chart
        if (ps[index].bt_remaining - tq > 0)
        {
            ps[index].bt_remaining -= tq;
            current_time += tq;
        }
        else
        {
            current_time += ps[index].bt_remaining;
            ps[index].bt_remaining = 0;
            completed++;
            ps[index].ct = current_time;
            ps[index].tat = ps[index].ct - ps[index].at;
            ps[index].wt = ps[index].tat - ps[index].bt;
            ps[index].rt = ps[index].start_time - ps[index].at;
            sum_tat += ps[index].tat;
            sum_wt += ps[index].wt;
            sum_rt += ps[index].rt;
        }
        for (int i = 1; i < n; i++)
        {
            if (ps[i].bt_remaining > 0 && ps[i].at <= current_time && !visited[i])
            {
                queue[++rear] = i;
                visited[i] = true;
            }
        }
        if (ps[index].bt_remaining > 0)
        {
            queue[++rear] = index;
        }
        if (front > rear)
        {
            for (int i = 1; i < n; i++)
            {
                if (ps[i].bt_remaining > 0)
                {
                    queue[rear++] = i;
                    visited[i] = true;
                    break;
                }
            }
        }
    }
    max_completion_time = INT_MIN;
    for (int i = 0; i < n; i++)
        max_completion_time = findmax(max_completion_time, ps[i].ct);

    length_cycle = max_completion_time - ps[0].at;
    cpu_utilization = (float)(length_cycle - total_idle_time) / length_cycle;

    qsort((void *)ps, n, sizeof(struct process_struct), compare_pid);

    printf("\nProcess No.\tAT\tBT\tStart Time\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n", ps[i].pid, ps[i].at, ps[i].bt,
               ps[i].start_time, ps[i].ct, ps[i].tat, ps[i].wt, ps[i].rt);
    }

    printf("\nAverage Turn Around time= %.2f", (float)sum_tat / n);
    printf("\nAverage Waiting Time= %.2f", (float)sum_wt / n);
    printf("\nAverage Response Time= %.2f", (float)sum_rt / n);
    printf("\nThroughput= %.2f", n / (float)length_cycle);
    printf("\nCPU Utilization(Percentage)= %.2f", cpu_utilization * 100);
    
    // Print Gantt Chart
    printf("\n\nGantt Chart:\n");
    for (int i = 0; i < gc_index; i++)
    {
        printf("| P%d ", gantt_chart[i]);
    }
    printf("|\n");
    return 0;
}

// #include<stdio.h>
// #include<limits.h>
// #include<stdbool.h> //for bool datatype
// #include <stdlib.h> //for qsort
// struct process_struct
// {
//  int pid;
//  int at;
//  int bt;
//  int ct,wt,tat,rt,st;
//  int bt_remaining;
// }ps[100];

// int findmax(int a, int b)
// {
//  return a>b?a:b;
// }
// int comparatorAT(const void * a, const void *b)
// {
//  int x =((struct process_struct *)a) -> at;
//  int y =((struct process_struct *)b) -> at;
//  if(x<y)
//  return -1; // No sorting
//  else if( x>=y) // = is for stable sort
//  return 1; // Sort
// }

// int comparatorPID(const void * a, const void *b)
// {
//  int x =((struct process_struct *)a) -> pid;
//  int y =((struct process_struct *)b) -> pid;
//  if(x<y)
//  return -1; // No sorting
//  else if( x>=y)
//  return 1; // Sort
// }
// int main()
// {

//  int n,index;
//  int cpu_utilization;
//  //queue<int> q;

//  bool visited[100]={false},is_first_process=true;
//  int current_time = 0,max_completion_time;
//  int completed = 0,tq, total_idle_time=0,length_cycle;

//  printf("Enter total number of processes: ");
//  scanf("%d",&n);
//  int queue[100],front=-1,rear=-1;
//  float sum_tat=0,sum_wt=0,sum_rt=0;

//  for(int i=0;i<n;i++)
//  {
//  printf("\nEnter Process %d Arrival Time: ",i);
//  scanf("%d",&ps[i].at);
//  ps[i].pid=i;
//  }

//  for(int i=0;i<n;i++)
//  {
//  printf("\nEnter Process %d Burst Time: ",i);
//  scanf("%d",&ps[i].bt);
//  ps[i].bt_remaining= ps[i].bt;
//  }

//  printf("\nEnter time quanta: ");
//  scanf("%d",&tq);

//  //sort structure on the basis of Arrival time in increasing order
//  qsort((void *)ps,n, sizeof(struct process_struct),comparatorAT);
//  // q.push(0);
//  front=rear=0;
//  queue[rear]=0;
//  visited[0] = true;

//  while(completed != n)
//  {
//  index = queue[front];
//  //q.pop();
//  front++;

//  if(ps[index].bt_remaining == ps[index].bt)
//  {
//  ps[index].st = findmax(current_time,ps[index].at);
//  total_idle_time += (is_first_process == true) ? 0 : ps[index].st - current_time;
//  current_time = ps[index].st;
//  is_first_process = false;

//  }
//  if(ps[index].bt_remaining-tq > 0)
//  {
//  ps[index].bt_remaining -= tq;
//  current_time += tq;
//  }
//  else
//  {
//  current_time += ps[index].bt_remaining;
//  ps[index].bt_remaining = 0;
//  completed++;
//  ps[index].ct = current_time;
//  ps[index].tat = ps[index].ct - ps[index].at;
//  ps[index].wt = ps[index].tat - ps[index].bt;
//  ps[index].rt = ps[index].st - ps[index].at;
//  sum_tat += ps[index].tat;
//  sum_wt += ps[index].wt;
//  sum_rt += ps[index].rt;

//  }
//  //check which new Processes needs to be pushed to Ready Queue from Input list
//  for(int i = 1; i < n; i++)
//  {
//  if(ps[i].bt_remaining > 0 && ps[i].at <= current_time && visited[i] == false)
//  {
//  //q.push(i);
//  queue[++rear]=i;
//  visited[i] = true;
//  }
//  }
//  //check if Process on CPU needs to be pushed to Ready Queue
//  if( ps[index].bt_remaining> 0)
//  //q.push(index);
//  queue[++rear]=index;

//  //if queue is empty, just add one process from list, whose remaining burst time > 0
//  if(front>rear)
//  {
//  for(int i = 1; i < n; i++)
//  {
//  if(ps[i].bt_remaining > 0)
//  {
//  queue[rear++]=i;
//  visited[i] = true;
//  break;
//  }
//  }
//  }
//  } //end of while

//  //Calculate Length of Process completion cycle
//  max_completion_time = INT_MIN;

//  for(int i=0;i<n;i++)
//  max_completion_time = findmax(max_completion_time,ps[i].ct);

//  length_cycle = max_completion_time - ps[0].at; //ps[0].start_time;

//  cpu_utilization = (float)(length_cycle - total_idle_time)/ length_cycle;
//  //sort so that process ID in output comes in Original order (just for interactivity- Not needed otherwise)
//  qsort((void *)ps,n, sizeof(struct process_struct),comparatorPID);
//  //Output
//  printf("\nProcess No.\tAT\tCPU Burst Time\tStart Time\tCT\tTAT\tWT\tRT\n");
//  for(int i=0;i<n;i++)

// printf("%d\t\t%d\t%d\t\t%d\t\t%d\t%d\t%d\t%d\n",i,ps[i].at,ps[i].bt,ps[i].start_time,ps[i].ct,ps
// [i].tat,ps[i].wt,ps[i].rt);
//  printf("\n");
//  printf("\nAverage Turn Around time= %.2f",(float)sum_tat/n);
//  printf("\nAverage Waiting Time= %.2f",(float)sum_wt/n);
//  printf("\nAverage Response Time= %.2f",(float)sum_rt/n);
//  printf("\nThroughput= %.2f",n/(float)length_cycle);
//  printf("\nCPU Utilization(Percentage)= %.2f",cpu_utilization*100);
//  return 0;
// }

// // #include<stdio.h>
// // #include<stdbool.h>
// // #include<stdlib.h>
// // // #include<limits.h>

// // struct Process
// // {
// //     int pid;
// //     float at;
// //     float bt;
// //     float st;
// //     float ct;
// //     float rt;
// //     float tat;
// //     float wt;
// // };

// // int compareAT(const void *a, const void *b)
// // {
// //     int x = ((struct Process *)a)->at;
// //     int y = ((struct Process *)a)->at;
// //     if(x < y)
// //         return -1;  //no sorting
// //     else if(x >= 1) //sort
// //         return 1;
// // }

// // int main()
// // {
// //     int n, front , rear;
// //     float tq;
// //     queue<int>q;
// //     bool visited[n] = {false};

// //     printf("Enter no of processes:\n");
// //     scanf("%d", &n);
// //     struct Process p[n];
// //      for (int i = 0; i < n; i++)
// //     {
// //         printf("\nEnter Process %d Arrival Time and Burst Time: ", i);
// //         scanf("%f%f", &p[i].at, &p[i].bt);
// //         p[i].pid = i;
// //     }

// //    printf("Enter time Quanta\n");
// //    scanf("%f", &tq);
// //    //sort struct on basis of arrival time
// //     qsort((void*) p, n, sizeof(struct Process), compareAT);
// //     //queue.push(0);
// //     front = rear = 0;
// //     //queue[rear] = 0;
// //     q[rear] =0;
// //     visited[0] = true;

// //     return 0;

// // }