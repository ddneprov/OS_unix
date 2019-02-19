#include <stdio.h>

int main() {
    __pid_t a,b;
    char str;


    a = getpid();
    b = getppid();

    printf("чтобы вывести pid нажмите 1\n чтобы вывесли ppid нажмите 2\n");
    str = (char)getchar();
    switch (str)
    {
        case '1':
            printf("My pid = %d", (int)a);
            break;
        case '2':
            printf("My ppid = %d", (int)b);
	    break;
	default:
	    printf("Error");
    }

    return 0;
}


