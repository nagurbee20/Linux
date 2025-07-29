#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>



/* Allocated in data segment */
static int gdata = 111;

int main(int argc, char *argv[])
{
    int istack = 222;
    pid_t childPid;
    /* Allocated in stack segment */

    switch (childPid = fork()) {
        case -1:
            printf("\n Fork() error");
            exit(-1);
        case 0:
            printf("\n I am child process\n");
            gdata *= 3;
            istack *= 3;
            printf("\n pid = (%d), gdata = (%d), istack = (%d)\n",getpid(),gdata,istack);
            sleep(5);
            break;
        
        default:
            printf("\n I am parent process\n");
            printf("\n pid = (%d), gdata = (%d), istack = (%d)\n",getpid(),gdata,istack);
            sleep(5);
        break;
    }
    /* Give child a chance to execute */
    /* Both parent and child come here */
    exit(0);
}

