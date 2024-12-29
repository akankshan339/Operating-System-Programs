#include<stdio.h>
#include<unistd.h>

int main()
{
//Replace curernt process with "ls" command
execlp("ls","ls",NULL);
printf("execlp failed.\n");
return 0;
}
