#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int status;

    pid_t pid = fork();
    if (pid < 0) {
        printf("error fork");
        exit(1);
    }
    if (pid == 0) {
        waitpid(0, &status, 0); // Wait for the child process to exit
        fprintf(stdout, "Hello\n");




    } else {
        fprintf(stdout, "WORLD\n");

        
    }
        close(1);
        system("leaks a.out");
        exit(1);

    // Execute leaks command only once after all processes have completed

    return 0;
}