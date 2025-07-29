/*
dup() system call - application, to write the output to a file instead of screen.
*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

void main(){
    int fd;
    fd = open("newFile.log", O_RDWR | O_CREAT, 0767);
    if (fd == -1){
        printf("\n open() was failed - errno = (%d)\n",errno);
        perror("ERROR:");
    }
    else
    {
        printf("\n open() system call executed successfully\n");
    }


    close(1);
    dup(fd);

    printf("\n Output not written to screen, rather written to file using dup() system call\n");
}

