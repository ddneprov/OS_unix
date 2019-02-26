#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd, result;
    size_t size;

    char resstring[14];
    char name[] = "u3.fifo";
    
    (void)umask(0);

    if (mknod(name, S_IFIFO | 0666, 0) < 0) {
        printf("Can\'t create FIFO\n");
        exit(-1);
    }
    printf( "READ data from FIFO\n");

    if ((fd = open(name, O_RDONLY)) < 0) {
        printf("Can\'t open FIFO for reading\n");
        exit(-1);
    }
    size = read(fd, resstring, 14);
    if (size < 0) {
        printf("Can\'t read string\n");
        exit(-1);
    }
    printf("READ from FIFO: %s\n", resstring);
    close(fd);
    return 0;
}
