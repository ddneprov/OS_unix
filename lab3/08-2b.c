/* Программа 2 для иллюстрации работы с семафорами */

/* Эта программа получает доступ к одному системному семафору
и увеличивает его значение на 1, чтобы разблокировать программу 1 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>

int main()
{

    int semid; 

    char pathname[] = "08-2a.c"; 
    key_t key; 

    struct sembuf mybuf;

   

    if((key = ftok(pathname,0)) < 0){
        printf("Can\'t generate key\n");
        exit(-1);
    }

    if((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0){
        printf("Can\'t get semid\n");
        exit(-1);
    } 


    mybuf.sem_op = 1;
    mybuf.sem_flg = 0;
    mybuf.sem_num = 0;

    if(semop(semid, &mybuf, 1) < 0){
        printf("Can\'t wait for condition\n");
        exit(-1);
    }

    printf("Set condition\n");
    return 0;
}