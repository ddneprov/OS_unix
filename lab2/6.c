#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[], char* envp[])
{
    int fd[2], result;
    size_t size;
    char resstring[14];
    /* Попытаемся создать pipe */
    if (pipe(fd) < 0) {
        /* Если создать pipe не удалось, печатаем об этом сообщение и прекращаем работу */
        printf("Can\'t create pipe\n");
        exit(-1);
    }
    /* Порождаем новый процесс */
    result = fork();
    if (result < 0) {
    
        /* Если создать процесс не удалось, сообщаем об этом и завершаем работу */
        printf("Can\'t fork child\n");
        exit(-1);
    } else if (result > 0) {
        /* Мы находимся в родительском процессе*/
        close(fd[0]);
        printf("I'm parent \n");
        dup2(fd[1], 1);
        execle("/bin/ls", "ls", 0, envp);
    } else {
        close(fd[1]);
        dup2(fd[0], 0);
        printf("Im child");
    }
    return 0;
}
