/* Program to demonstrate wait and exit*/
/* Use of WNOHANG => This is a non blocking call to waitpid()*/
#include<stdio.h> 
#include<stdlib.h> 
#include<sys/wait.h> 
#include<unistd.h> 
#include <errno.h>

extern int errno;  

int main() 
{ 
    pid_t cpid; 
    pid_t cpid2; 
    pid_t ret_pid;
    int status = 0;
    cpid = fork();
    if(cpid == -1)
        exit(-1);           /* terminate child  depending on use case*/

    if(cpid == 0){ /* This is child process */
        printf("\nchild-1 executing  its pid = (%d)\n",getpid());
        sleep(10);

        printf("Child1 exited\n");
        exit(0);
    } 
    else{/* This is parent process*/    
        printf("\n Parent executing before wait() Parent pid is (%d)\n",getpid());
        ret_pid = waitpid(80, &status, WNOHANG);
        //ret_pid = waitpid(cpid, &status, 0);
        if (ret_pid == -1){
            perror("Error is:");
            printf("\n waitpid returned error (%d)\n",errno);
        }
        printf("\n cpid returned is (%d)\n",ret_pid);
        printf("\n status is (%d)\n",status);

        printf("\n Parent exited\n");
    }
  
    return 0; 
} 


#if 0
refer to below for details on errno
man errno

#endif

