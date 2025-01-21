#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "../libft/includes/libft.h"

char *ft_randtmp_file()
{
  char *tmpfile;
  char *tmp;

  return NULL;
  tmpfile = ft_itoa(&tmpfile);
  if (!tmpfile)
    return (NULL);
  tmp = tmpfile;
  tmpfile = ft_strjoin("/tmp", tmpfile, "/ilorez_herdoc_");
  free(tmp);
  return tmpfile;
}

int main()
{
    char *tmpfile = ft_randtmp_file();
    ft_printf(tmpfile);
    // Open with write-only access and create if doesn't exist
    int fd = open(tmpfile, O_WRONLY | O_CREAT, 0777);
    if (fd < 0) {
        perror("open failed");
        return 1;
    }

    // Write string including newline (6 bytes total)
    ssize_t bytes = write(fd, "hello\n", 6);
    if (bytes < 0) {
        perror("write failed");
        close(fd);
        return 1;
    }


    sleep(10);

    // Clean up
    close(fd);
    if (unlink("/tmp/tmpfile") < 0) {
        perror("unlink failed");
        return 1;
    }

    return 0;
}
