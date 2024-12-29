#include<stdio.h>
#include<unistd.h>

int main()
{
    int pid = fork();
    printf("PID = %d ", pid);
    if(pid < 0)
    {
        printf("Process cannot be created :\n");
    }
    else if( pid == 0)
    {
        printf("Child Process created...\n%d", getpid());

    }
    else
    {
        printf("Parent Process is running \n");
    }
    return 0;
}