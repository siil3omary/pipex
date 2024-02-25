/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:55:06 by aelomari          #+#    #+#             */
/*   Updated: 2024/02/25 22:38:49 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	checkall(t_pipex *pipex)
{
	ft_checkfile(pipex);
	ft_checkcmd(pipex, 2);
	ft_checkcmd(pipex, 3);
}
void	pipexinit(int ac, char **av, char **env, t_pipex *pipex)
{
	pipex->acs = ac;
	pipex->avs = av;
	pipex->envs = env;
	pipex->cmd1 = NULL;
	pipex->cmd2 = NULL;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(int ac, char **av, char **env)
{
	t_pipex	*pipex;

	if (ac == 5)
	{
		pipex = malloc(sizeof(t_pipex));
		if (!pipex)
			return (0);
		pipexinit(ac, av, env, pipex);
		checkall(pipex);
		pipe(pipex->pip);
		pipex->pid = fork();
		if (!pipex->pid)
		{
			close(pipex->pip[0]);
			dup2(pipex->infile_fd, STDIN_FILENO);
			dup2(pipex->pip[1], STDOUT_FILENO);
			close(pipex->infile_fd);
			close(pipex->pip[0]);
			execve(pipex->cmd1, pipex->cmd1args, env);
			exit(1);
		}
		else
		{
			dup2(pipex->outfile_fd, STDOUT_FILENO);
			dup2(pipex->pip[0], STDIN_FILENO);
			close(pipex->outfile_fd);
			close(pipex->pip[1]);
			execve(pipex->cmd2, pipex->cmd2args, env);
			waitpid(pipex->pid, NULL, 0);
		}
		system("leaks pipex");
	}
	else
		errorarg();
	return (0);
}
