// C program to implement one side of FIFO 
// This side writes first, then reads 
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 

int main() 
{ 
	int fd; 

	// FIFO file path 
	char * myfifo = "/tmp/myfifo"; 
	char  arr2[80]; 

	// Creating the named file(FIFO) 
	// mkfifo(<pathname>, <permission>) 
	mkfifo(myfifo, 0660); 
	// Open FIFO for write only 
	fd = open(myfifo, O_WRONLY); 

	while (1) 
	{ 
            printf("\nEnter string to be sent via fifo\n");
	    fgets(arr2, 80, stdin); 

	    // Write the input arr2ing on FIFO 
	    // and close it 
	    write(fd, arr2, strlen(arr2)+1); 
	} 
	close(fd); 
	return 0; 
} 


