/*
Demonstrate Orphan process
*/

#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() 
{ 
  
    pid_t id;
    printf("Parent Process : Executed by parent process before fork() - PID = (%d)\n",getpid()); 
    id = fork();  // from this point of code, the child and parent process both execute 
    if (id < 0 ){
        printf("\nfork failed\n");
        exit(-1);
    }
    if(id > 0){ // Parent process, killing before child executes
        printf("\nParent process exited\n");
        return (0);

    }else
    { // Child process
        printf("\nChild process executing\n");
        sleep(10);
        printf("\nI am child process,  id value is (%d)\n",id) ;
        printf("\nchild process id is (%d)\n",getpid());
    }
  
    return 0; 
} 

