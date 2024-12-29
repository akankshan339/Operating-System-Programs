#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main()
{
pid_t pid =fork();
if(pid < 0)
	printf("Fork Failed:\n");
else if(pid == 0)
{
	execlp("ls","ls","-l",(char*)NULL);
	printf("Child Process Completed.\n");
	exit(0);
}
else{
	wait(NULL);
	printf("Parent Process waited until child completed.\n");
}
return 0;
}
