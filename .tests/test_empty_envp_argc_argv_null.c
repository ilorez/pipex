#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
  char *argv[2];
  char str[] = "ls";

  argv[0] = str;
  argv[1] = NULL;
  int pid = fork();
  if (pid == 0)
  {
    execve("/usr/bin/ls", argv, NULL);
    perror("error");
  }
  else 
  {
    wait(NULL);
    printf("i'm parent");
  }

}
