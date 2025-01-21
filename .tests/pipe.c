#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int main() {
    int pipe_fd[2];
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    // Create the pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // First write and read
    printf("\n=== First write and read ===\n");
    const char *message1 = "Hello, this is the first message!\n";
    printf("Writing: %s", message1);
    
    if (write(pipe_fd[1], message1, strlen(message1)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    // Read from pipe
    bytes_read = read(pipe_fd[0], buffer, BUFFER_SIZE);
    if (bytes_read == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    buffer[bytes_read] = '\0';  // Null terminate the string
    printf("Read: %s", buffer);

    // Second write and read
    printf("\n=== Second write and read ===\n");
    const char *message2 = "This is the second message in the same pipe!\n";
    printf("Writing: %s", message2);
    
    if (write(pipe_fd[1], message2, strlen(message2)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    // Read from pipe again
    bytes_read = read(pipe_fd[0], buffer, BUFFER_SIZE);
    if (bytes_read == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    buffer[bytes_read] = '\0';  // Null terminate the string
    printf("Read: %s", buffer);

    // Close pipe file descriptors
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    return 0;
}
