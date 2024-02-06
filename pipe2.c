#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(void)
{
    pid_t pid;
    int pfd[2];

    pipe(pfd);
    pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "Fork failed\n");
        return (1);
    }
    else if (pid == 0)
    {
        close(pfd[0]); // close unused end (the reading end) of the pipe
        // write(pfd[1], "this is a new message", 22);
        dup2(pfd[1], 1);
        close(pfd[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(pfd[1]);
        dup2(pfd[0], 0);
        close(pfd[0]);
        char str[22];
        // read(pfd[0], str, 22);
        read(0, str, 22);
        printf("parent received: %s\n", str);
        wait(NULL);
    }
    return EXIT_SUCCESS;
}
