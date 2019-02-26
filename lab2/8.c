#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int fd[2], result;
    size_t size;
    char resultString[1000000];

    if (pipe(fd) < 0)
    {
        printf("Can\'t create pipe\n");
        exit(-1);
    }
    //порождаю процесс
    result = fork();

    if (result < 0)
    {
        printf("Can\'t fork child\n");
        exit(-1);
    }
    else if (result > 0)
    {
    /*Parent*/
        close(fd[0]);
        do
        {
            size = write(fd[1], "9", 1);
            result++;
        }while(size == 1);
        close(fd[1]);
    }
    else
    {
    /*Children*/
        close(fd[1]);
        sleep(7);
        size = read(fd[0], resultString, 1000000);
        printf("%ld", size);
        close(fd[0]);
    }
    return 0;
}
