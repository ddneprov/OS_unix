#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int args, char *argv[], char *envp[]) {
    pid_t mark;
    mark = fork();

    if (mark == -1)
    {
        printf("error\n");
    }
    else if (mark == 0)
    {
        printf("child\n");
        (void) execle("/bin/cat", "/bin/ls", "n4.c", 0, envp);
    }
    else
    {
        printf("parent\n");
    }
    return 0;
}

