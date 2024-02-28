#include "pipex_bonus.h"

void child_process1(t_pipex *pipex)
{
    char *cmd[] = {"/bin/ls","-la",NULL}; 
    // dup2(pipex->pipe_fd[1], 1);
    // dup2(pipex->infile_fd, 0);


    execve(cmd[0], cmd, pipex->envs);
}
void child_process2(t_pipex *pipex)
{
    char *cmd[] = {"/bin/ls","-la",NULL}; 
    // dup2(pipex->pipe_fd[0],1);
    // dup2(pipex->outfile_fd, 0);

    
    execve(cmd[0] , cmd, pipex->envs);
}
 void initcmds(t_pipex *pipex)
 {

 }

 void initpipex(t_pipex *pipex , int ac, char **av, char **env)
 {
    pipex->acs = ac;
    pipex->avs = av;
    pipex->envs = env;
    pipex->infile_fd = open(pipex->avs[1] , O_RDONLY);
    pipex->outfile_fd = open(pipex->avs[pipex->acs - 1], O_CREAT | O_RDONLY | O_TRUNC , 0644);
    if(pipex->infile_fd == -1)
    {
        perror("aa");
        exit(200);
    }
    // printf("%d\n", pipex->outfile_fd);
    if(pipex->outfile_fd == -1)
    {
        perror("bb");
        exit(1);
    initcmds(pipex);
 }
    }
int main(int ac, char **av  , char  **env)
{
    if(ac >= 5){
    t_pipex *pipex;
    pipex = (t_pipex *)malloc(sizeof(t_pipex));
    initpipex(pipex , ac, av, env);
    pipex->i = 0;
    while (pipex->i < ac - 3)
    {
        if(pipe(pipex->pipe_fd) == -1)
        return 0;
        pipex->pid[pipex->i] = fork();
        if(pipex->pid[pipex->i] == -1)
        return 0;
        if(!pipex->pid[pipex->i])
        {
            if (!pipex->i)
            child_process1(pipex);
            else
            child_process2(pipex);


        }
        else
        {
            waitpid(pipex->pid[pipex->i], &pipex->status , 0);
        }
        pipex->i++;
    }
    
        
    }else
    perror("hello") ;
}