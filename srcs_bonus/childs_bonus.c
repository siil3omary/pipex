/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:20:07 by aelomari          #+#    #+#             */
/*   Updated: 2024/04/15 22:37:58 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	if (!pipex->cmd)
	{
		free_all(pipex->cmd);
		exit(127);
	}
	execve(pipex->cmd[0], pipex->cmd, pipex->envs);
	free_all(pipex->cmd);
	exit(127);
}

void	secend_child(t_pipex *pipex)
{
	close(pipex->pipe_fd[0]);
	dup2(pipex->pipe_fd[1], 1);
	close(pipex->pipe_fd[1]);
	pipex->cmd = check_cmd(pipex->avs[pipex->index], pipex);
	if (!pipex->cmd)
	{
		free_all(pipex->cmd);
		exit(0);
	}
	execve(pipex->cmd[0], pipex->cmd, pipex->envs);
	free_all(pipex->cmd);
	exit(0);
}

void	first_child(t_pipex *pipex)
{
	close(pipex->pipe_fd[0]);
	dup2(pipex->infile_fd, 0);
	dup2(pipex->pipe_fd[1], 1);
	close(pipex->pipe_fd[1]);
	pipex->cmd = check_cmd(pipex->avs[pipex->index], pipex);
	if (!pipex->cmd)
	{
		free_all(pipex->cmd);
		exit(0);
	}
	execve(pipex->cmd[0], pipex->cmd, pipex->envs);
	free_all(pipex->cmd);
	exit(0);
}
