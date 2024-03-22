/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:10:30 by aelomari          #+#    #+#             */
/*   Updated: 2024/03/22 01:28:16 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putchar(char c)
{
	write(2, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n > 9)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
}

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
				if (pipex->infile_fd == -1){
					pipex->infile_fd = STDIN_FILENO;
					
				}
				close(pipex->pipe_fd[0]);
				dup2(pipex->infile_fd, 0);
				dup2(pipex->pipe_fd[1], 1);
				close(pipex->pipe_fd[1]);
				pipex->cmd = check_cmd(pipex->avs[pipex->index], pipex);
				execve(pipex->cmd[0], pipex->cmd, pipex->envs);
				free_all(pipex->cmd);
				free(pipex);
				exit(1);
			}
			else if (pipex->index != ac - 2)
			{
				close(pipex->pipe_fd[0]);
				dup2(pipex->pipe_fd[1], 1);
				close(pipex->pipe_fd[1]);
				pipex->cmd = check_cmd(pipex->avs[pipex->index], pipex);
				execve(pipex->cmd[0], pipex->cmd, pipex->envs);
				free_all(pipex->cmd);
				free(pipex);
				exit(1);
			}
			else if (pipex->index == ac - 2)
			{
				close(pipex->pipe_fd[1]);
				if (pipex->outfile_fd == -1)
					ft_putstr_fd("hello\n", 2);
				dup2(pipex->outfile_fd, 1);
				close(pipex->pipe_fd[0]);
				pipex->cmd = check_cmd(pipex->avs[pipex->index], pipex);
				execve(pipex->cmd[0], pipex->cmd, pipex->envs);
				free(pipex);
				free_all(pipex->cmd);
				exit(1);
			}
		}
		else
		{
			close(pipex->pipe_fd[1]);
			dup2(pipex->pipe_fd[0], 0);
			close(pipex->pipe_fd[0]);
		}
		pipex->index++;
	}
	while (wait(pipex->status) == -1)
		waitpid(pipex->pid, pipex->status, WNOHANG);
	free(pipex);
	return (0);
}
