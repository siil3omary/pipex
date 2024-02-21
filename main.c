#include <stdio.h>
#include <unistd.h>
int main()
{
    char *av[] ={"/bin/ls", "\0"};
    char *env[] = {"\0"};

printf("av[0]: %s\n", av[0]);
printf("av[1]: %s\n", av[1]);
    execve("/bin/ls", av, env);


}