/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipx.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:32:17 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/07 15:54:41 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int int main(int argc, char *argv[], char *envp[]) 
{
  int pid;
  int fd[2];
  char *line;
  
  if (pipe(fd) == -1)
  {
    perror("pipe");
    return EXIT_FAILURE;
  }
  pid = fork();
  if (pid == -1)
  {
    perror("fork");
    return EXIT_FAILURE;
  }
  if (pid == 0)
  {
    close(fd[0]);
    char *command = ft_strjoin(argv[2], " ");
    command = ft_strjoin(command, argv[1]);
    char **cmd_args = ft_split(command, ' ');
    dup2(fd[1], 1);
    if(execve(argv[2], cmd_args, envp)==-1)
    {
      perror("execve");
      exit(1);
    }
  }
  else {
    close(fd[1]);
    line = get_next_line(fd[0]);
    while (line)
    {
      if (fork() == 0)
      {
        int fd1 = open(argv[4], O_WRONLY | O_CREAT, 0777);
        if (fd1 == -1)
        {
          perror("open");
          exit(1);
        }
        dup2(fd1, 1);
        if(execve(argv[3], cmd_args, envp)==-1)
        {
          perror("execve");
          exit(1);
        }
      }
      free(line);
      line = get_next_line(fd[0]);
    }
    free(line);
  }
  return EXIT_SUCCESS;
}


