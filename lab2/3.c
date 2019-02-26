#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
   int     fd;
   size_t  size;
   char    string[14]; /*1*/

   if((fd = open("myfile", /*1*/O_RDONLY)) < 0){
     printf("Can\'t open file\n");
     exit(-1);
   }

   size = read(fd, string, 14);

   if(size < 0){
     printf("Can\'t read\n");
     exit(-1);
   } else
       printf("%s\n", string);

   if(close(fd) < 0){
     printf("Can\'t close file\n");
   }

   return 0;
}
