#include<stdio.h>
#include<unistd.h>

int main()
{
pid_t pid =fork();
if(pid < 0)
	printf("Fork Failed:\n");
else if(pid == 0)
	printf("Child Process: My PID %d, My Parent PID %d\n",getpid(),getppid());
else
	printf("Parent Process: My PID %d, My Child PID %d\n",getpid(),pid);
return 0;
}
