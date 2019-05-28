#include <ntsid.h>
#include <fcntl.h>
#include <zconf.h>
#include <sys/mman.h>
#include <stdio.h>

int main(void)
{
    // Счетчик запусков на обе программы
    struct Counter {
        int first;
        int second;
        int sum;
    } *ptr;

    int fd = open("shared.dat", O_RDWR | O_CREAT, 0666);
    if(fd == -1){
        printf("File open failed!\n");
        return 1;
    }
    ftruncate(fd, 1);

    ptr = (struct Counter*)mmap(NULL, 1, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    close(fd);
    if( ptr == MAP_FAILED ){
        printf("Mapping failed!\n");
        return 2;
    }

    // Увеличиваем счетчик запусков текущей программы и общее количество запусков
    ptr->second++;
    ptr->sum++;

    printf("First: %d Second: %d Sym: %d", ptr->first, ptr->second, ptr->sum);
    munmap((void *)ptr, 1);
    return 0;
}