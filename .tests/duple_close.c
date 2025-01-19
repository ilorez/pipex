#include <stdio.h>

#include <unistd.h>

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdint.h>
# include <stddef.h>

# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>

int main()
{
  int fd = open("./README.md", O_RDONLY, 0777);
  int re;

  printf("fd: %d\n", fd);
  printf("errno: %d\n", errno);
  re = close(fd);
  printf("fd: %d\n", fd);
  printf("errno: %d\n", errno);
  printf("re: %d\n", re);
  re = close(fd);
  printf("fd: %d\n", fd);
  printf("re: %d\n", re);
  printf("errno: %d\n", errno);
}
