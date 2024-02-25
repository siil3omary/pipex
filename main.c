#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int status;
    char *s[] = {"/bin/ls", NULL};
    char *s1[] = {"/bin/ls", NULL};
    pid_t pid = fork();
    if(pid < 0)
        printf("fork error");
    
        // waitpid(0 , &status, 0);
    
    if(pid == 0)
    {
        printf("Hello from child%d\n  " , getpid());


        execve("/bin/ls" , s , NULL);

        exit(1);
        
    }else
    {
        
        // wait(NULL );
        // waitpid(0, &status, 0);
        execve("/bin/ls" , s1, NULL);
// exit(1);
    }

    // system("leaks a.out");
}   