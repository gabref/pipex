#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    pid = fork();
    // parent process
    printf("Hello, i am the parent process! PID: %d, and my child's PID is %d.\n", getpid(), pid);
    return (0);
}
