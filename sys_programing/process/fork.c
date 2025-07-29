#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>


int main()
{
	pid_t id;

	id = fork();

	if(id < 0)
	{
		printf("fork() is failed\n");
		exit(-1);
	}
	if(id > 0)
	{
		printf("Parent Id :child process id is :%d\n",id);
	}
	else
	{
		printf("I am child process id is :%d\n",id);
		printf("child process id is :%d\n",getpid());
		printf("the craetor of child process  is :%d\n",getppid());
	}
return 0;
}
