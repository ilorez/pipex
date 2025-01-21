#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    // Allocate memory in parent process
    char *str = malloc(100);
    strcpy(str, "Hello from shared memory!");
    printf("Parent (PID %d) - Initial string: %s at address: %p\n", 
           getpid(), str, (void*)str);
    
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork failed");
        free(str);
        exit(1);
    }
    
    if (pid == 0) {
        // Child process
        printf("\nChild (PID %d) - Before free, string: %s at address: %p\n", 
               getpid(), str, (void*)str);
        
        free(str);  // Free only affects child's memory
        printf("Child - Memory freed\n");
        
        // Try to use str after free (dangerous, just for demonstration)
        printf("Child - After free, memory at address %p might contain garbage\n", 
               (void*)str);
        
        exit(0);
    } else {
        // Parent process
        wait(NULL);  // Wait for child to finish
        
        printf("\nParent - After child exits, string is still available: %s at address: %p\n", 
               str, (void*)str);
        
        free(str);  // Parent must free its own memory
        printf("Parent - Memory freed\n");
    }
    
    return 0;
}
