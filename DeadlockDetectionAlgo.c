#include <stdio.h>
int main()
{
    int n, m;
    printf("Enter the number of processes and resources: ");
    scanf("%d %d", &n, &m);
    
    int alloc[n][m], request[n][m], availableresource[m], avail[m], work[m], marked[n];
    for (int i = 0; i < n; i++)
    {
        marked[i] = 0;
    }
    printf("Enter the total number of each resource:\n");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &availableresource[i]);
    }
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }
    printf("Enter the request matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &request[i][j]);
        }
    }
    
    for (int j = 0; j < m; j++)
    {
        avail[j] = availableresource[j];
        for (int i = 0; i < n; i++)
        {
            avail[j] -= alloc[i][j];
        }
    }
    for (int j = 0; j < m; j++)
    {
        work[j] = avail[j];
    }
    for (int i = 0; i < n; i++)
    {
        int count = 0;
        for (int j = 0; j < m; j++)
        {
            if (alloc[i][j] == 0)
            {
                count++;
            }
            else
            {
                break;
            }
        }
        if (count == m)
        {
            marked[i] = 1;
        }
    }
    for (int i = 0; i < n; i++)
    {
        int can_be_processed = 1;
        if (marked[i] != 1)
        {
            for (int j = 0; j < m; j++)
            {
                if (request[i][j] > work[j])
                {
                    can_be_processed = 0;
                    break;
                }
            }
            if (can_be_processed)
            {
                marked[i] = 1;
                for (int j = 0; j < m; j++)
                {
                    work[j] += alloc[i][j];
                }
            }
        }
    }
    int deadlock = 0;
    for (int i = 0; i < n; i++)
    {
        if (marked[i] != 1)
        {
            deadlock = 1;
            printf("Process P%d is in deadlock\n", i);
        }
    }
    if (!deadlock)
    {
        printf("No deadlock possible\n");
    }
}