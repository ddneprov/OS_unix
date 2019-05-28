#include <ntsid.h>
#include <fcntl.h>
#include <zconf.h>
#include <sys/mman.h>
#include <stdio.h>

int main(void)
{
    struct A {
        double f;
        double f2;
    } *ptr, *tmpptr;

    int fd = open("mapped.dat", O_RDWR | O_CREAT, 0666);
    if(fd == -1){
        printf("File open failed!\n");
        return 1;
    }

    size_t length = 100000*sizeof(struct A);
    ftruncate(fd,length);

    ptr = (struct A*)mmap(NULL, length, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    close(fd);
    if( ptr == MAP_FAILED ){
        printf("Mapping failed!\n");
        return 2;
    }
    tmpptr = ptr;
    for(int i = 1; i <=100000; i++){
        tmpptr->f = i;
        tmpptr->f2 = tmpptr->f*tmpptr->f;
        tmpptr++;
    }
    munmap((void *)ptr, length);
    return 0;
}