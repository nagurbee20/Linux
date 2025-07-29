#include <stdlib.h>
#include <stdio.h>//for standard i/p and o/p 
#include <unistd.h>//for system calss tread and write
#include <fcntl.h> //file controls like O_RDONLY


int main() 
{ 
  int fd, sz; 
  char buf[30] = {0};
  
  fd = open("input.txt", O_RDONLY); 
  if (fd < 0){
      perror("Error:"); exit(1); 
  } 
  
  sz = read(fd, buf, 25); 
  printf("call 1 - called read. fd = %d,  %d bytes  were read.\n", fd, sz); 
  buf[sz] = '\0'; //adding null pointer
  printf("Read bytes are as follows: \n<%s>\n", buf); 

  printf("\n Note the next set of bytes read from file, it is continuos\n");

  sz = read(fd, buf, 30); //ofset will increase in kernel code
  printf("call 2 - called read. fd = %d,  %d bytes  were read.\n", fd, sz); 
  buf[sz] = '\0'; 
  printf("Read bytes are as follows:\n<%s>\n", buf); 

  sz = read(fd, buf, 25); 
  printf("call 3 - called read. fd = %d,  %d bytes  were read.\n", fd, sz); 
  if(sz == 0){
      printf("EOF Reached\n");
  }


  close(fd);



} 

