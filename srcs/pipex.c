/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:55:06 by aelomari          #+#    #+#             */
/*   Updated: 2024/02/25 15:14:20 by aelomari         ###   ########.fr       */
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
		t_pipex *pipex;

	if (ac == 5)
	{
		pipex = malloc(sizeof(t_pipex));
		if (!pipex)
			return (0);
		pipexinit(ac, av, env, pipex);
		checkall(pipex);
		pipex->pid = fork();
		if (!pipex->pid)
		{
			printf("fromc child \n");
			execve(pipex->cmd1, pipex->cmd1args, env);
			close(1);
		}
		else
		{
			printf("from parent \n");
			execve(pipex->cmd2, pipex->cmd2args, env);
		}
	}
	else
		errorarg();
	system("leaks pipex");
	return (0);
}
// }0
