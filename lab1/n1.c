#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int args, char *argv[], char *envp[]) {
    pid_t a,b;

    a = getpid(); // значение текущего процесса
    b = getppid(); // значение родительского процесса

    printf("My pid = %d, my ppid = %d", (int)a, (int)b);
    return 0;
}
