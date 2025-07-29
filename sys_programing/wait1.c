/* Program to demonstrate wait and exit*/

#include<stdio.h> 
#include<stdlib.h> 
#include<sys/wait.h> 
#include<unistd.h> 
  
int main() 
{ 
    pid_t cpid; 
    int status = 0;
    cpid = fork();
    printf("cpid is %d\n",cpid);
    if(cpid == -1)
        exit(-1);           /* terminate child */

    if(cpid == 0){
        printf("\nchild executing first its pid = (%d)\n",getpid());
        sleep(20);
        printf("Child pid = %d\n", getpid()); 
        exit(1);
    } 
    else{    
        printf("\n Parent executing before wait()\n");
       // cpid = wait(NULL); 
        cpid = wait(&status); 
        printf("\n wait() in parent done\nParent pid = %d\n", getpid()); 
        printf("\n cpid returned is (%d)\n",cpid);
        printf("\n status is (%d)\n",status);
    }
  
    return 0; 
} 


#if 0
Process termination status (int) 16 bit number
1. status value if  child process has normal exit/termination
   15......8    |     7......0
   XXXXXXXX     |     XXXXXXXX 
   exitStaus    |     0


2. killed by signal
    15......8    |     7   ......0
    unused       |     X   termination signal
                       |
                       |-----> core dump flag


#endif

