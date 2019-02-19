#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() 
{
    pid_t mark;
    mark = fork();
   
   

    if (mark == -1)
        printf("error\n");
    else if (mark == 0)
    {
	printf("child\n %d");
    }
    else
        printf("parent\n");
    

    return 0;
}

