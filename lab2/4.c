#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
   int     fd[2];
   size_t size;
   char     string[] = "Hello, Danila Dneprov!";
   char  resstring[22];

// пытаемся создать pipe
   if(pipe(fd) < 0){
     printf("Can\'t open pipe\n");
     exit(-1);
   }

// пробуем записать строчку в 14 байт, т.е. всю строчку с признаком конца строки
   size = write(fd[1], string, 22);

   if(size != 22){
   //если записалось меньше - сообщаем об ошибке
     printf("Can\'t write all string to pipe\n");
     exit(-1);
   }

// пробуем прочитать из pip'а 14 байт в другой массив, т.е. всю записанную строку
   size = read(fd[0], resstring, 22);
   if(size < 0){
      printf("Can\'t read string from pipe\n");
      exit(-1);
   }


// печать
   printf("%s\n", resstring);

   close(fd[0]);
   close(fd[1]);

   return 0;
}
