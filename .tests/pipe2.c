#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/resource.h>

void test_efault() {
    printf("\n=== Testing EFAULT ===\n");
    int *invalid_fd = NULL;
    if (pipe(invalid_fd) == -1) {
        printf("EFAULT demonstration: %s\n", strerror(errno));
    }
}

void test_einval() {
    printf("\n=== Testing EINVAL ===\n");
    int pipefd[2];
    // Try to use invalid flags with pipe2()
    if (pipe2(pipefd, -1) == -1) {
        printf("EINVAL demonstration: %s\n", strerror(errno));
    }
}

void test_emfile() {
    printf("\n=== Testing EMFILE ===\n");
    // Get current soft limit
    struct rlimit rlim;
    getrlimit(RLIMIT_NOFILE, &rlim);
    printf("Current soft limit: %ld\n", (long)rlim.rlim_cur);
    
    // Array to store pipe file descriptors
    int **pipes = malloc(sizeof(int*) * rlim.rlim_cur);
    int i;
    
    // Try to open more pipes than allowed
    for(i = 0; i < rlim.rlim_cur; i++) {
        pipes[i] = malloc(sizeof(int) * 2);
        if (pipe(pipes[i]) == -1) {
            printf("EMFILE demonstration at fd %d: %s\n", i, strerror(errno));
            break;
        }
    }
    
    // Cleanup
    for(int j = 0; j < i; j++) {
        close(pipes[j][0]);
        close(pipes[j][1]);
        free(pipes[j]);
    }
    free(pipes);
}

int main() {
    printf("Testing various pipe errors:\n");
    
    test_efault();
    test_einval();
    test_emfile();
    
    printf("\nNote: ENFILE and ENOPKG are system-wide limits and harder to demonstrate safely.\n");
    printf("ENFILE requires hitting system-wide open file limit.\n");
    printf("ENOPKG requires specific kernel configuration.\n");
    
    return 0;
}
