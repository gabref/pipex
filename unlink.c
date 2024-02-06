#include <stdio.h>
#include <unistd.h>

int main()
{
    if (unlink("example.txt") == 0)
        printf("file successfully deleted");
    else
        printf("error deleting file");
    return (0);
}
