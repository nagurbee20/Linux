#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
	int fd;
	size_t len;
	char *addr;

	fd = shm_open("/shm_1",O_CREAT|O_RDWR,0660);
	if(fd == -1)
	{
		printf("error creating shm\n");
		perror("shm_open");
		exit(-1);
	}
	printf("open shm successfull\n");

	len = strlen(argv[1]);
	if(ftruncate(fd,len) == -1)
	{
		perror("ftruncate\n");
		exit(-1);
	}

	addr = mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(addr == MAP_FAILED)
	{
		perror("mmap\n");
		exit(-1);
	}
	if(close(fd)==-1)
	{
		perror("close\n");
	}
	memcpy(addr,argv[1],len);
	exit(0);
}


		
