/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:53:31 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/10 16:15:57 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "pipx.h"
#include "libft.h"

// dup a FD and close it
t_bool  ft_change_fd(int fd, int to)
{
  if (dup2(fd, to) == -1)
  {
    perror("dup2");
    exit(1);
  }
  close(fd);
  return true;
}

// get paths & split it from envp
char **ft_get_paths(char *envp[])
{
  char **paths;
  char *tmp;

  paths = NULL;
  while (envp)
  {
    if (ft_strncmp(*envp, "PATH=", 5) == 0)
    {
      paths = ft_split(*envp, ':');
      break;
    }
    envp++;
  }
  if (!paths)
  {
    // set errno
    ft_printf("error not fonded");
    exit(1);
  }
  tmp = paths[0];
  paths[0] = ft_strdup(tmp+5);
  free(tmp);
  return paths;
}

// get path can be founded
char *ft_get_right_path(char *cmd, char **paths)
{
  char *path;

  path = NULL;
  while (*paths)
  {
    path = ft_strjoin(ft_strjoin(paths[0], "/"), cmd);
    if (access(path, F_OK | X_OK) == 0)
      return path;
    free(path);
    paths++;
  }
  return (ft_strdup(cmd));
}

// main functions
int main(int argc, char *argv[], char *envp[]) 
{
  int fd1[2]
  int fd2[2]
  int infile;
  int outfile;
  int read;


  read = infile;
  while(i=2, i < argc-1, i++)
  {
    cmds = split(argv[i]);
    path = get_right_path(paths);
    pipe(fd1);
    id = fork();
    if (id==0)
    {
        dup2(fd1[1], 1);
        dup2(read, 0);
        close(read);
        close(fd[1]);
        close(fd[0]);
        execve(path, cmds, envp);
    }
    close(fd1[1])
    wait(null);
    read = fd1[0];
    free(cmds);
    free(path);
  }
}

