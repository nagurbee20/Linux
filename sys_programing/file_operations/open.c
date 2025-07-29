#include<stdio.h>
#include<fcntl.h>
#include<errno.h>


void main()
{
int fd;

//fd = open("startup",O_CREAT|O_RDONLY|O_EXCL);
fd = open("startup1",O_CREAT|O_RDONLY,S_IRWXU|S_IRWXG|S_IROTH);
if(fd == -1)
{
printf("\n open was failed - errno :%d\n",errno);
perror("ERROR");
}
else
{printf("\n open() is success , fd of open is %d ",fd);
}

}
