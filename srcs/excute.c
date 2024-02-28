/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:06:27 by aelomari          #+#    #+#             */
/*   Updated: 2024/02/28 13:48:04 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	pipexinit(int ac, char **av, char **env, t_pipex *pipex)
{
	pipex->acs = ac;
	pipex->avs = av;
	pipex->envs = env;
	pipex->cmd1 = NULL;
	pipex->cmd2 = NULL;
}

void	child_process(t_pipex *pipex)
{
	dup2(pipex->infile_fd, STDIN_FILENO);
	dup2(pipex->pip[1], STDOUT_FILENO);
	close(pipex->infile_fd);
	close(pipex->pip[0]);
	execve(pipex->cmd1, pipex->cmd1args, pipex->envs);
	exit(EXIT_FAILURE);
}
void	child1_process(t_pipex *pipex)
{
	waitpid(pipex->pid, &pipex->status, 0);
	close(pipex->pip[1]);
	dup2(pipex->outfile_fd, STDOUT_FILENO);
	dup2(pipex->pip[0], STDIN_FILENO);
	close(pipex->outfile_fd);
	close(pipex->pip[0]);
	execve(pipex->cmd2, pipex->cmd2args, pipex->envs);
}
