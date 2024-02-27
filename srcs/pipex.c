/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:55:06 by aelomari          #+#    #+#             */
/*   Updated: 2024/02/27 16:06:01 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	checkall(t_pipex *pipex)
{
	ft_checkfile(pipex);
	ft_checkcmd(pipex, 2);
	ft_checkcmd(pipex, 3);
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
			child_process(pipex);
		else
			parent_process(pipex);
	}
	else
		errorarg();
	return (0);
}
