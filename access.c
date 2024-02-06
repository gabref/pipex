#include <stdio.h>
#include <unistd.h>

int main()
{
    if (access("example.txt", R_OK) != -1)
        printf("i have permission");
    else
        printf("i do not have permission");
    return (0);
}
