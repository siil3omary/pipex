#include "../includes/pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pipex *pipex;
	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	int i = 0;
	pipexinit(ac, av, env, pipex);
	while (i < ac - 3)
	{
		pipe(pipex->pip);

		checkall(pipex);
		pipex->pid1 = fork();
		if (pipex->pid1 == 0)
		{
			close(pipex->pip[0]);
			dup2(pipex->infile_fd, STDIN_FILENO);
			dup2(pipex->pip[1], STDOUT_FILENO);
			close(pipex->infile_fd);
			close(pipex->pip[1]);
			execve(pipex->cmd1, pipex->cmd1args, pipex->envs);
			exit(EXIT_FAILURE);
		}
		else
		{
			// waitpid(pipex->pid1, &pipex->status, 0);
			pipex->pid2 = fork();
			if (pipex->pid2 == 0)
			{
				close(pipex->pip[1]);
				dup2(pipex->outfile_fd, STDOUT_FILENO);
				dup2(pipex->pip[0], STDIN_FILENO);
				close(pipex->outfile_fd);
				close(pipex->pip[0]);
				execve(pipex->cmd2, pipex->cmd2args, pipex->envs);
			}
			else
			{
				free_all(pipex->cmd2args);
				free_all(pipex->cmd1args);
				waitpid(pipex->pid2, &pipex->status, 0);
			}
		}
		i++;
	}
	return (0);
}