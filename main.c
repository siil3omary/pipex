#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int status;
    pid_t pid;

    pid = fork();
    if(pid < 0)
    {
        printf("error fork");
        exit(1);
    }
    waitpid(pid, &status, 0);
    if(pid == 0)
    {
        printf("hello from %d", getpid());
        close(1);
    }else{
        printf("hello from %d", getpid());


    }
    system("leaks a.out");
}