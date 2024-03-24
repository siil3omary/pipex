/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:10:30 by aelomari          #+#    #+#             */
/*   Updated: 2024/03/24 22:39:46 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pipex	*pipex;

	if (ac < 5 || (ac == 2 && ft_strcmp(av[1], "--help")))
	{
		if (ft_strcmp(av[1], "--help"))
		{
			ft_putstr_fd("\033[32mUsage: \e[0m", 1);
			ft_putstr_fd("./pipex file1 cmd1 cmd2 file2", 1);
			exit(EXIT_FAILURE);
		}
		else
		{
			ft_putstr_fd("\033[31mpipex: \e[0m", 2);
			ft_putstr_fd("Bad argument", 2);
			ft_putstr_fd("\n\t --help for Usage\n", 2);
			exit(EXIT_FAILURE);
		}
	}
	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	initstrct(pipex, ac, av, env);
	openfiles(pipex);
	pipex->index = 2;
	while (pipex->index < ac - 1)
	{
		pipe(pipex->pipe_fd);
		pipex->pid = fork();
		if (pipex->pid == -1)
		{
			ft_putstr_fd("\033[31mpipex: \e[0m", 2);
			ft_putstr_fd("fork failed", 2);
			exit(EXIT_FAILURE);
		}
		if (pipex->pid == 0)
		{
			if (pipex->index == 2)
			{
				close(pipex->pipe_fd[0]);
				dup2(pipex->infile_fd, 0);
				dup2(pipex->pipe_fd[1], 1);
				close(pipex->pipe_fd[1]);
				pipex->cmd = check_cmd(pipex->avs[pipex->index], pipex);
				if (!pipex->cmd)
				{
					exit(0);
				}
				execve(pipex->cmd[0], pipex->cmd, pipex->envs);
				exit(127);
				free_all(pipex->cmd);
				// free(pipex);
			}
			else if (pipex->index != ac - 2)
			{
				close(pipex->pipe_fd[0]);
				dup2(pipex->pipe_fd[1], 1);
				close(pipex->pipe_fd[1]);
				pipex->cmd = check_cmd(pipex->avs[pipex->index], pipex);
				if (!pipex->cmd)
				{
					exit(0);
				}
				execve(pipex->cmd[0], pipex->cmd, pipex->envs);
				free_all(pipex->cmd);
				exit(0);
				exit(123);
			}
			else if (pipex->index == ac - 2)
			{
				close(pipex->pipe_fd[1]);
				dup2(pipex->outfile_fd, 1);
				close(pipex->pipe_fd[0]);
				pipex->cmd = check_cmd(pipex->avs[pipex->index], pipex);
				if (!pipex->cmd)
				{
					exit(127);
				}
				execve(pipex->cmd[0], pipex->cmd, pipex->envs);
				free_all(pipex->cmd);
				// free(pipex);
			}
		}
		else
		{
			// exit_status = WEXITSTATUS(pipex->status);
			close(pipex->pipe_fd[1]);
			dup2(pipex->pipe_fd[0], 0);
			close(pipex->pipe_fd[0]);
		}
		pipex->index++;
	}
	free(pipex);
	return (0);
}
