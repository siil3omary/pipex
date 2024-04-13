/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:10:30 by aelomari          #+#    #+#             */
/*   Updated: 2024/04/13 21:03:41 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pipex	*pipex;

	if (ac != 5 || (ac == 2 && ft_strcmp(av[1], "--help")))
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
		pipex->status = WEXITSTATUS(pipex->status);
		


	
		printf("%d\n", pipex->status);
	// while ((waitpid(pipex->pid, &pipex->status, 0) != -1))
	// 	if (pipex->status == 0)
	// 		pipex->status = WEXITSTATUS(pipex->status);
	// printf("%d" , pipex->status);
	exit(pipex->status);
	
	free(pipex);
	return (0);
}
