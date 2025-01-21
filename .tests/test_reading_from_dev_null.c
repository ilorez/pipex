#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    char buff[10];

    dup2(open("/dev/null", O_RDONLY), STDIN_FILENO); // Redirect standard output to the file
    printf("num: %d\n", read(STDIN_FILENO, buff, 10)); // Write to the file
    write(1, buff, 10);
    return 0;
}
