#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd, result;
    size_t size;
    char resstring[14];
    char name[]="u3.fifo";

    (void)umask(0);

    printf("File FIFO is created\n");
    printf("I'll write data to fifo\n");

    if((fd = open(name, O_WRONLY)) < 0){
        printf("Can\'t open FIFO for writing\n");
        exit(-1);
    }
    size = write(fd, "hello", 14);
    printf("I wrote to fifo\n");
    if(size != 14) {
        printf("Can\'t write FIFO\n");
        exit(-1);
    }
    close(fd);
    return 0;
}
