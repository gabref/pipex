#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void callexecve()
{
    char *const args[] = { "ls", NULL };
    char *const envp[] = { NULL };

    execve("/bin/ls", args, envp);
    perror("execve");
    exit(EXIT_FAILURE);
}

int main(void)
{
    pid_t pid;

    printf("Hi I am the main process. My PID is: %d\n", getpid());
    pid = fork();
    if (pid == -1)
        printf("Error while forking\n");
    else if (pid == 0)
    {
        printf("I am the child. but now a new parent. My PID is: %d --- my child's PIDis: %d\n", getpid(), pid);
    }
    else if (pid > 1)
    {
        printf("I am the parent. My PID is: %d --- my child's PID is: %d\n", getpid(), pid);
        waitpid(pid, NULL, 0);
        printf("parent: got back the control\n");
    }
    return (0);
}
