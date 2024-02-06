#include <stdio.h>
#include <unistd.h>

int main()
{
    int pfd[2];
    char str[20];

    pipe(pfd);
    write(pfd[1], "hello", 5);
    read(pfd[0], str, 2);
    str[2] = '\0';
    printf("%s\n", str);
}
