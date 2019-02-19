#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int args, char *argv[], char *envp[])
{
    (void) execle("/bin/cat", "/bin/cat", "n4.c", 0, envp);
    printf("ERROR");
    _exit(-1);
}
