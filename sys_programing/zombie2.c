/*
Demonstrate Zombie process
run command on terminal - ps aux | grep Z

Note: A zombie process can be removed by its parent by executing a wait/waitpid
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
    if(id > 0){ /*Parent process*/
        sleep(10);
        printf("\n run ps aux | grep Z\n");
        waitpid(id,NULL,0);
        printf("\nParent Process: I have created child process withID = (%d)\n",id);
        sleep(6);
        printf("\n Paren process exited\n");

    }else
    { /* Child process*/
        sleep(5);
        printf("\nchild process id is (%d)\n",getpid());
        printf("\nThe creator of child process is (%d)\n",getppid());
    }
  
    return 0; 
} 

