#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int args, char *argv[], char *envp[]) {
    printf("Hello, World!\n");

    pid_t a,b;
    int sum = 0;

    fork();

    sum++;
    a = getpid();
    b = getppid();

    printf("My pid = %d, my ppid = %d, sum = %d\n", (int)a, (int)b, sum);
    return 0;
}

