/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:10:30 by aelomari          #+#    #+#             */
/*   Updated: 2024/03/25 02:33:39 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_pipex(t_pipex *pipex)
{
	if (pipex->pid == 0)
	{
		if (pipex->index == 2)
			first_child(pipex);
		else if (pipex->index != pipex->acs - 2)
			secend_child(pipex);
		else if (pipex->index == pipex->acs - 2)
			last_child(pipex);
	}
	else
	{
		close(pipex->pipe_fd[1]);
		dup2(pipex->pipe_fd[0], 0);
		close(pipex->pipe_fd[0]);
	}
}

void	fork_error(void)
{
	ft_putstr_fd("\033[31mpipex: \e[0m", 2);
	ft_putstr_fd("fork failed", 2);
	exit(EXIT_FAILURE);
}

void	last_child(t_pipex *pipex)
{
	close(pipex->pipe_fd[1]);
	dup2(pipex->outfile_fd, 1);
	close(pipex->pipe_fd[0]);
	pipex->cmd = check_cmd(pipex->avs[pipex->index], pipex);
	execve(pipex->cmd[0], pipex->cmd, pipex->envs);
	free_all(pipex->cmd);
}

void	secend_child(t_pipex *pipex)
{
	close(pipex->pipe_fd[0]);
	dup2(pipex->pipe_fd[1], 1);
	close(pipex->pipe_fd[1]);
	pipex->cmd = check_cmd(pipex->avs[pipex->index], pipex);
	execve(pipex->cmd[0], pipex->cmd, pipex->envs);
	free_all(pipex->cmd);
}

void	first_child(t_pipex *pipex)
{
	close(pipex->pipe_fd[0]);
	dup2(pipex->infile_fd, 0);
	dup2(pipex->pipe_fd[1], 1);
	close(pipex->pipe_fd[1]);
	pipex->cmd = check_cmd(pipex->avs[pipex->index], pipex);
	execve(pipex->cmd[0], pipex->cmd, pipex->envs);
	free_all(pipex->cmd);
}

void	error_args(char **av)
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

int	main(int ac, char **av, char **env)
{
	t_pipex	*pipex;

	if (ac < 5 || (ac == 2 && ft_strcmp(av[1], "--help")))
		error_args(av);
	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	initstrct(pipex, ac, av, env);
	openfiles(pipex);
	while (pipex->index < ac - 1)
	{
		pipe(pipex->pipe_fd);
		pipex->pid = fork();
		if (pipex->pid == -1)
			fork_error();
		ft_pipex(pipex);
		pipex->index++;
	}
	while ((wait(&pipex->status)) != -1)
	{
		pipex->status = WEXITSTATUS(pipex->status);
	}
	exit(pipex->status);
	free(pipex);
	return (0);
}
