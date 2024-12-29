#include<stdio.h>
#include<unistd.h>

int main()
{
pid_t pid =fork();
if(pid < 0)
	printf("Fork Failed:\n");
else if(pid == 0)
	printf("This is Child Process.\n");
else
	printf("This is Parent Process.\n");
return 0;
}


