// #include "pipex_bonus.h"

// void child_process1(t_pipex *pipex)
// {

//     char *cmd[] = {"/bin/cat","-" ,NULL}; 
//     dup2(pipex->infile_fd, 0);
//     dup2(pipex->pipe_fd[1], 1);

//     execve(cmd[0], cmd, pipex->envs);
//         printf("error1");
// }
// void child_process2(t_pipex *pipex)
// {
//     char *cmd[] = {"/bin/ls","-la",NULL}; 
//     if(pipex->i == pipex->acs - 4)
//     {
//         dup2(pipex->pipe_fd[0], 0);
//         dup2(pipex->outfile_fd, 1);
//     }else  {
//     dup2(pipex->pipe_fd[0], 0);
//     dup2(pipex->pipe_fd[1], 1);
//     }

//     execve(cmd[0] , cmd, pipex->envs);
//         printf("error2");

// }
//  void initcmds(t_pipex *pipex)
//  {

//  }

//  void initpipex(t_pipex *pipex , int ac, char **av, char **env)
//  {
//     pipex->acs = ac;
//     pipex->avs = av;
//     pipex->envs = env;
//     pipex->infile_fd = open(pipex->avs[1] , O_RDONLY);
//     pipex->outfile_fd = open(pipex->avs[pipex->acs - 1], O_CREAT | O_RDONLY | O_TRUNC , 0644);
//     if(pipex->infile_fd == -1)
//     {
//         perror("aa");
//         exit(200);
//     }
//     // printf("%d\n", pipex->outfile_fd);
//     if(pipex->outfile_fd == -1)
//     {
//         perror("bb");
//         exit(1);
//     initcmds(pipex);
//  }
//     }
// int main(int ac, char **av  , char  **env)
// {
//     if(ac >= 5){
//     t_pipex *pipex;
//     pipex = (t_pipex *)malloc(sizeof(t_pipex));
//     initpipex(pipex , ac, av, env);
//     pipex->i = 0;
//     while (pipex->i < ac - 3)
//     {
//         if(pipe(pipex->pipe_fd) == -1)
//         return 0;
//         pipex->pid[pipex->i] = fork();
//         if(pipex->pid[pipex->i] == -1)
//         return 0;
//         if(!pipex->pid[pipex->i])
//         {
//             if (!pipex->i)
//             child_process1(pipex);
//             else
//             child_process2(pipex);


//         }
//         else
//         {
//             waitpid(pipex->pid[pipex->i], &pipex->status , 0);
//         }
//         pipex->i++;
//     }
    
        
//     }else
//     perror("hello") ;
// }

#include "pipex_bonus.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

void child_process1(t_pipex *pipex) {
    char *cmd[] = {"/bin/cat", NULL, NULL}; 
    dup2(pipex->infile_fd, 0);
    dup2(pipex->pipe_fd[1], 1);
    
    if (execve(cmd[0], cmd, pipex->envs) == -1) {
        perror("execve failed");
        exit(EXIT_FAILURE);
    }
}

void child_process2(t_pipex *pipex) {
    char *cmd[] = {"/usr/bin/grep", "a", NULL}; 
    if (pipex->i == pipex->acs - 4) {
        close(pipex->pipe_fd[1]);
        dup2(pipex->pipe_fd[0], 0);
        dup2(pipex->outfile_fd, 1);
        close(pipex->pipe_fd[0]);

    } else {
        close(pipex->pipe_fd[0]);
        dup2(pipex->pipe_fd[0], 0);
        dup2(pipex->pipe_fd[1], 1);
        close(pipex->pipe_fd[1]);
        close(pipex->pipe_fd[0]);
    }
    
    if (execve(cmd[0], cmd, pipex->envs) == -1) {
        perror("execve failed");
        exit(EXIT_FAILURE);
    }
}

void initpipex(t_pipex *pipex, int ac, char **av, char **env) {
    pipex->acs = ac;
    pipex->avs = av;
    pipex->envs = env;
    pipex->infile_fd = open(pipex->avs[1], O_RDONLY);
    pipex->outfile_fd = open(pipex->avs[pipex->acs - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (pipex->infile_fd == -1) {
        perror("open infile_fd failed");
        exit(EXIT_FAILURE);
    }
    if (pipex->outfile_fd == -1) {
        perror("open outfile_fd failed");
        exit(EXIT_FAILURE);
    }
}

int main(int ac, char **av, char **env) {
    if (ac >= 5) {
        t_pipex *pipex;
        pipex = (t_pipex *)malloc(sizeof(t_pipex));
        if (pipex == NULL) {
            perror("malloc failed");
            exit(EXIT_FAILURE);
        }
        
        initpipex(pipex, ac, av, env);
        pipex->i = 0;
        
        while (pipex->i < ac - 3) {
            if (pipe(pipex->pipe_fd) == -1) {
	                perror("pipe failed");
                exit(EXIT_FAILURE);
            }
            
            pipex->pid[pipex->i] = fork();
            if (pipex->pid[pipex->i] == -1) {
                perror("fork failed");
                exit(EXIT_FAILURE);
            }
            
            if (!pipex->pid[pipex->i]) {
                if (!pipex->i)
                    child_process1(pipex);
                else
                    child_process2(pipex);
            } else {
                waitpid(pipex->pid[pipex->i], &pipex->status, 0);
            }
            pipex->i++;
        }
        free(pipex);
    } else {
        perror("Usage: pipex_bonus file1 cmd1 cmd2 file2");
    }
    return 0;
}
