#include "pipex_bonus.h"
void child_process1(t_pipex *pipex)
{

}
void child_process2(t_pipex *pipex)
{
    
}
 initpipex(t_pipex *pipex , int ac, char **av, char **env)
 {
    pipex->acs = ac;
    pipex->avs = av;
    pipex->envs = env;
    pipex->infile_fd = open(pipex->avs[1] , O_RDONLY);
    pipex->outfile_fd = open(pipex->avs[pipex->acs - 1], O_CREAT | O_RDONLY | O_TRUNC , 0644);
    if(pipex->infile_fd == -1)
    {
        perror("");
        exit(1);
    }
    if(pipex->outfile_fd)
    {
        perror("");
        exit(1);
    }
    initcmds(pipex);
 }
 void initcmds(t_pipex *pipex)
 {
    
 }
int main(int ac, char **av  , char **env)
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
        pipex->pid = fork();
        if(pipex->pid == -1)
        return 0;
        if(pipex->pid == 0)
        {
            if (pipex->i == 0)
            child_process1(pipex);
            else
            child_process2(pipex);


        }else
        {
            waitpid(pipex->pid, &pipex->status , 0);
        }

    }
    
        
    }
}