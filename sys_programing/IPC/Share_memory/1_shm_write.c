#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
  int fd;
  size_t len;
  char *addr;

  fd = shm_open("/shm_1", O_RDWR | O_CREAT, 0660);
  if (fd == -1){
    printf("\nError creating shm\n");
    perror("shm_open");
    exit(-1);
  }
  /* Open existing object */

  printf("\n shm open success\n");
  len = strlen(argv[1]);
  if (ftruncate(fd, len) == -1){
      perror("ftruncate");
      exit(-1);
  }

  printf("Resized to %ld bytes\n", (long) len);
  addr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (addr == MAP_FAILED){
    perror("mmap");
    exit(-1);
  }

  if (close(fd) == -1){
      perror("close");
  }
  memcpy(addr, argv[1], len);
  exit(0);
}

