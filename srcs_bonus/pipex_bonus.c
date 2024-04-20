/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:10:30 by aelomari          #+#    #+#             */
/*   Updated: 2024/04/20 20:57:23 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	t_pipex	*pipex;
	int		st;
	int		proccess_id;

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
	while ((proccess_id = wait(&pipex->status)) != -1)
	{
		if (proccess_id == pipex->pid)
			st = WEXITSTATUS(pipex->status);
	}
	return (free_all(pipex->cmd), st);
}
