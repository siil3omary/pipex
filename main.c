#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *s[] = {"/bin/ls", NULL};
    char *s1[] = {"/bin/ls", NULL};
    pid_t pid = fork();
    if(pid < 0){
        printf("fork error");

    }
    waitpid(0 , NULL, 0 );
    if(pid == 0)
    {
        printf("Hello from child%d\n  " , getpid());
        execve("/bin/ls" , s, NULL);
        exit(1);
        
    }else
    {
        printf("\nhello from parent %d" , getpid());
        execve("/bin/cat" , s1, NULL);
    }
    system("leaks a.out");
}   