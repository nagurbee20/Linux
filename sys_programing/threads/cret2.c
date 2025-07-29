#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>


void *ThreadFunc(void *arg)
{
	char *str = (char *)arg;
	printf("ThreadFunc: %s ,printed in ThreadFunc pic = (%d)\n",str,getpid());
	(void)sleep(15);
	printf("\n threadFunc : exiting now \n");
	pthread_exit(0);
}

int main()
{
	pthread_t t1;
	int s;
	void *res;

	s = pthread_create(&t1,NULL,ThreadFunc,"Hello World");

	if(s!=0)
		perror("Thread Create Error\n");
	printf("Main method:Message from main(),pid =(%d)\n",getpid());

	sleep(5);
/*	s = pthread_join(t1,&res);
	if(s!=0)
		 perror("Thread Create Error\n");*/
	printf("\n Main thread: after sleep 5 sec\n");

	exit(0);
//	pthread_exit(0);

}
