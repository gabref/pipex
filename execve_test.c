#include <unistd.h>
#include <stdio.h>

int main()
{
    printf("PID before the execve is: %d\n", getpid());
    char *const args[] = { "ls", NULL };
    char *const envp[] = { NULL  };

    execve("/bin/ls", args, envp);
    perror("execve");
    printf("PID after the execve is: %d\n", getpid());
    return (1);
}
