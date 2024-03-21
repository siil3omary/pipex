/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:10:30 by aelomari          #+#    #+#             */
/*   Updated: 2024/03/21 05:43:59 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pipex	*pipex;
	int		st;

	if (ac < 5)
	{
		if (ft_strcmp(av[1], "--help"))
		{
			ft_putstr_fd("\033[32mUsage: \e[0m", 1);
			ft_putstr_fd("./pipex file1 cmd1 cmd2 file2", 1);
			exit(EXIT_FAILURE);
		}
		ft_putstr_fd("\033[31mpipex: \e[0m", 2);
		ft_putstr_fd("Bad argument", 2);
		ft_putstr_fd("\n\t --help for help\n", 2);
		exit(EXIT_FAILURE);
	}
	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	//  init args
	initstrct(pipex, ac, av, env);
	// pipex excute
	pipe(pipex->pipe_fd);
	openfiles(pipex);
	while (pipex->index < ac - 3)
	{
		pipex->pid = fork();
		if (pipex->pid == -1)
		{
			ft_putstr_fd("\033[31mpipex: \e[0m", 2);
			ft_putstr_fd("fork failed", 2);
			exit(EXIT_FAILURE);
		}
		if (pipex->pid == 0)
		{
			if (pipex->index == 0)
			{
				close(0);
				dup2(pipex->infile_fd, 0);
				dup2(pipex->pipe_fd[1], 1);
				close(pipex->pipe_fd[1]);
				close(pipex->infile_fd);
				pipex->cmd = check_cmd(pipex->avs[pipex->index + 2], pipex);
				printf("flag here");
				execve(pipex->cmd[0], pipex->cmd, pipex->envs);
				free_all(pipex->cmd);
				free(pipex);
				exit(1);
			}
			else
			{
				if (pipex->index == pipex->acs - 4)
				{
				close(0);
					close(pipex->pipe_fd[1]);
					dup2(pipex->outfile_fd, 1);
					dup2(pipex->pipe_fd[0], 0);
					close(pipex->pipe_fd[0]);
					close(pipex->outfile_fd);
					pipex->cmd = check_cmd(pipex->avs[pipex->index + 2], pipex);
					ft_putstr_fd(pipex->cmd[0], 2);
					execve(pipex->cmd[0], pipex->cmd, pipex->envs);
					free(pipex);
					free_all(pipex->cmd);
					exit(1);
				}
				else
				{
				close(0);

					dup2(pipex->pipe_fd[0], 0);
					dup2(pipex->pipe_fd[1], 1);
					close(pipex->pipe_fd[0]);
					close(pipex->pipe_fd[1]);
					pipex->cmd = check_cmd(pipex->avs[pipex->index + 2], pipex);
					execve(pipex->cmd[0], pipex->cmd, pipex->envs);
					free(pipex);
					free_all(pipex->cmd);
					exit(1);
				}
			}
		}
		pipex->index++;
	}
	while (wait(&st) != -1)
		pipex->status = WEXITSTATUS(st);
	free(pipex);
	return (0);
}
