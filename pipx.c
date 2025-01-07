/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipx.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:32:17 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/07 08:14:45 by znajdaou         ###   ########.fr       */
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
  int fd1;
  int fd2;
  char *line;
  char *f_v;
  
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
    char **cmd_args = ft_split(argv[2], ' ');
    execve(cmd_args[0], cmd_args, envp);
    fd1 = open(argv[1], O_RONLY);
    free(line);
  }
  return EXIT_SUCCESS;
}


