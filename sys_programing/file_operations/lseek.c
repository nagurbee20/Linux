#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>


int main()
{

	int sz ,seek_pos = 0;

	char buf[100];
	int fd = open("input.txt",O_RDONLY);
	if(fd < 0)
	{
		perror("Error : \n");
		exit(1);
	}

	seek_pos = lseek(fd,0,SEEK_SET);

	printf("Initial offset position is  % d\n ",seek_pos);
	
	seek_pos = lseek(fd,2,SEEK_SET);

        printf("second offset position is  % d\n ",seek_pos);

	seek_pos = lseek(fd,10,SEEK_CUR);

        printf("SEEK_CUR offset position is  % d\n ",seek_pos);

	seek_pos = lseek(fd,2,SEEK_SET);

        printf("seek_set after seek_cur offset position is  % d\n ",seek_pos);

	sz = read(fd,buf,10);

	printf("\n read bytes from filr is %d \n",sz);
	buf[sz]='\0';
	printf("read buff as follows:%s\n ",buf);

	seek_pos = lseek(fd,0,SEEK_END);

	printf("seek end offset position is  % d\n ",seek_pos);

	strcpy(buf,"This is seek_end\n");
	write(fd,buf,strlen(buf));

	//printf("write buff as follows:%s\n ",buf);
	close(fd);
	return 0;
}
