#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

void *threadFunc(void *arg)
{
	char *str =  (char *) arg;
	printf("ThreadFunc : arguments passed are :%s,pid = (%d)\n",str,getpid());
	(void)sleep(2);
	printf("thradFun exiting now\n");
	return(0);
}

int main()
{
	pthread_t t1;
	int s;

	s = pthread_create(&t1,NULL,threadFunc,"Hello World");

	if(s !=0)
		perror("Thread eroor");
	printf("Main thread : Message from main(), pid(%d)\n",getpid());

	sleep(5);
	printf("main thread exiting now\n");

	exit(0);
}

	
