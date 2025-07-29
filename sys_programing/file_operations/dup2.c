/* 
dup2() - system call has more control over the duplicating file descriptor of user's choice.
dup2() automatically closes the oldfd(1st parameter), and duplicates newfd(2nd parameter) and assign it to oldfd
this means after dup2(), both newfd and oldfd refers to same file that was open by newfd
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

void main(){
    int fd;
    fd = open("newFile2.log", O_RDWR | O_CREAT, 0767);
    if (fd == -1){
        printf("\n open() was failed - errno = (%d)\n",errno);
        perror("ERROR:");
    }
    else
    {
        printf("\n open() system call executed successfully\n");
    }


    //int dup2(int oldfd, int newfd);
    dup2(fd,1); // newfd will be closed i.e. std output, later duplicate of oldfd, will be given to newfd
    /* after dup2 system call both oldfd and newfd points to same file newFile2.log in this example*/

    printf("\n Output not written to screen, rather written to file using dup2()\n");
}

