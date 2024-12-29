#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main()
{
pid_t pid1, pid2;
pid1 =fork();
if(pid1 < 0)
	printf("Fork Failed:\n");
else if(pid1 == 0)
{
	execlp("ls","ls","-l",(char*)NULL);
	printf("Child Process Completed.\n");
	exit(0);
}
else{
	wait(NULL);
	printf("Parent Process waited until child completed.\n");
	pid2= fork();
	if(pid2 <0)
	{
	printf("Fork Failed:\n");
	return -1;
	}
	else if(pid2 ==0)
	{
	printf("Child process 2 PID %d I am second child.\n", getpid());
	sleep(5);
	printf("Child Process 2 PID %d Work Done.\n",getpid());
	exit(0);
	}
	else
	{
	printf("Parent Process PID %d Existing Now.\n",getpid());
	exit(0);
	}
}
return 0;
}
