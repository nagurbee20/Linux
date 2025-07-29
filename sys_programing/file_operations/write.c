#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

int main()
{
	int sz;
	char buf[100];
	
	strcpy(buf,"This is example of O_APPEND");

	int fd = open("write.txt",O_CREAT|O_EXCL|O_WRONLY);
	if(fd < 0)
	{
		perror("Error:\n");
		exit(1);
	}
	printf("string length of buffer is %d ",(int)strlen(buf));
	sz = write(fd,buf,strlen(buf));

	printf("\nwrite written is %d ",sz);

	//int fd2;

	fd = open("input.txt",O_WRONLY|O_APPEND);

	if(fd < 0)
        {
                perror("Error:\n");
                exit(1);
        }
        printf("string length of buffer is %d ",(int)strlen(buf));
        sz = write(fd,buf,strlen(buf));

        printf("\nwrite written in input is %d ",sz);





	return 0;
}
