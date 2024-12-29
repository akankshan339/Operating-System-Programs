#include<stdio.h>

int main()
{
    int fd[2];
    int val = pipe(fd);
    if(val == -1)
    {

    }
    pid_t pid = fork();
    if(pid == 0)
    
    close(fd[0]);
    write(fd[1]);
    close(fd[1]);

    return 0;
}