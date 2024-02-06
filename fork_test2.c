#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = 9;
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf("hello, i am main process (before fork). My PID is: %d\n", getpid());
    pid = fork();
    printf("---------------------------------------\n");
    printf("hello, i am main process (after fork). My PID is: %d\n", getpid());
    if (pid < 0)
    {
        fprintf(stderr, "Fork 2 has failed\n");
        return (1);
    }
    else if (pid == 0)
        printf("Hello, i am the child process! My PID is: %d\n", getpid());
    else
        printf("Hello, i am the parent process! My PID is: %d and my child's PID is: %d\n", getpid(), pid);
    return (0);
}
