#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int status1, status2;
    pid_t pid, wait1, wait2;

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {  // Child
        printf("Child process: PID = %d\n", getpid());
        sleep(2);
        exit(42);
    }
    else {  // Parent
        // First wait - using wait()
        wait1 = wait(&status1);
        printf("First wait() returned PID: %d, status: %d\n", 
               wait1, WEXITSTATUS(status1));

        // Second wait - using waitpid() specifically for our child
        wait2 = waitpid(pid, &status2, 0);
        printf("waitpid(%d) returned: %d\n", pid, wait2);
        if (wait2 == -1) {
            perror("waitpid failed");
        }
    }

    return 0;
}
