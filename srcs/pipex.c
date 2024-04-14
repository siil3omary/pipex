/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:10:30 by aelomari          #+#    #+#             */
/*   Updated: 2024/04/14 17:43:54 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pipex	*pipex;
	int		exit_st;
	// int		i = 0;

	exit_st = 0;
	if (ac != 5 || (ac == 2 && ft_strcmp(av[1], "--help")))
		error_args(av);
	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	initstrct(pipex, ac, av, env);
	openfiles(pipex);
	// int last_pid;
	while (pipex->index < ac - 1)
	{
		pipe(pipex->pipe_fd);
		pipex->pid = fork();
		// if (pipex->index == ac - 2 && pipex->pid)
		// 	last_pid  =
		if (pipex->pid == -1)
			fork_error();
		ft_pipex(pipex);
		pipex->index++;
	}

	int status;
	int proccess_id;
	while (1)
	{
		proccess_id = wait(&status);
		if (proccess_id == pipex->pid)
			exit(WEXITSTATUS(status));
	}
	
	// i = 2;
	// while (i < ac - 1)
	// {
	// 	int *status   = NULL;
	// 	waitpid(pipex->pid, status, 0);
	// 	exit_st = WEXITSTATUS(pipex->status);
	// 	printf("%d \n" , exit_st);
	// 	i++;
	// }
	// exit(exit_st);
	// while ((waitpid(pipex->pid, &pipex->status, 0) != -1))
	// 		pipex->status = WEXITSTATUS(pipex->status);
	// printf("%d" , pipex->status);
	// exit(exit_st);
}
