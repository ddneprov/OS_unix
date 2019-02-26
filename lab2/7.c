#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
   int parentToChild[2], childToParent[2], result;

   size_t size;

   if(pipe(parentToChild) < 0){
     printf("Can\'t open pipe\n");
     exit(-1);
   }
   if(pipe(childToParent) < 0){
      printf("Can\'t open pipe\n");
      exit(-1);
   }

   result = fork();

   if(result < 0) {
      printf("Can\'t fork child\n");
      exit(-1);
   } else if (result > 0) {
      /* Parent process */

      //write to child
      close(parentToChild[0]);
      size = write(parentToChild[1], "Hello, child!", 14);

      if(size != 14){
         printf("Can\'t write to child\n");
         exit(-1);
      }

      close(parentToChild[1]);

      //read from child
      char  resstring[14];
      close(childToParent[1]);
      size = read(childToParent[0], resstring, 14);

      if(size < 0){
         printf("Can\'t read from child\n");
         exit(-1);
      }
      printf("Received hello from child:%s\n", resstring);
      close(childToParent[0]);

      printf("Parent exit\n");

   } else {
         /* Child process */

      //read from parent
      char  resstring[14];
      close(parentToChild[1]);
      size = read(parentToChild[0], resstring, 14);

      if(size < 0){
         printf("Can\'t read from from parent\n");
         exit(-1);
      }
      printf("Received hello from parent:%s\n", resstring);
      close(parentToChild[0]);


      //write to parent
      close(childToParent[0]);

      size = write(childToParent[1], "Hello, parent!", 14);

      if(size != 14){
         printf("Can\'t write to parent\n");
         exit(-1);
      }

      close(childToParent[1]);
      printf("Child exit\n");
   }

   return 0;
}
