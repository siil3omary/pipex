/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:10:30 by aelomari          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/19 21:00:50 by aelomari         ###   ########.fr       */
=======
/*   Updated: 2024/03/19 00:45:24 by aelomari         ###   ########.fr       */
>>>>>>> 8f696a1a5d2ee8c03c8c69bac95cca889daedae3
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	
	
	pipe(pipex->pipe_fd);
	openfiles(pipex);
	while (pipex->index < ac - 3)
	{
		pipex->pid = fork();
		if (pipex->pid == -1)
		{
			ft_putstr_fd("\033[31mpipex: \e[0m", 2);
			ft_putstr_fd("fork failed", 2);
			exit(EXIT_FAILURE);
		}
		if (pipex->pid == 0)
		{
			if (pipex->index == 0)
			{
				ft_putstr_fd("=========================================\n", 1);

				pipex->cmd = check_cmd(pipex->avs[pipex->index + 2], pipex);
				ft_putstr_fd("=========================================\n", 1);
<<<<<<< HEAD
					while (1)
	{
		/* code */
	}
=======
				system("leaks a.out");
>>>>>>> 8f696a1a5d2ee8c03c8c69bac95cca889daedae3
				execve(pipex->cmd[0], pipex->cmd, pipex->envs);
				printf("cmd: %s\n", pipex->cmd[0]);
				free_all(pipex->cmd);
				free(pipex);
<<<<<<< HEAD
				system("leaks a.out");
=======
>>>>>>> 8f696a1a5d2ee8c03c8c69bac95cca889daedae3
				exit(1);
			}
			else
			{
				pipex->cmd = check_cmd(pipex->avs[pipex->index + 2], pipex);
				ft_putstr_fd("=========================================\n", 1);
<<<<<<< HEAD
					while (1)
	{
		/* code */
	}
=======
				system("leaks a.out");
>>>>>>> 8f696a1a5d2ee8c03c8c69bac95cca889daedae3
				execve(pipex->cmd[0], pipex->cmd, pipex->envs);
				printf("cmd: %s %s\n", pipex->cmd[0], pipex->cmd[1]);
				free_all(pipex->cmd);
				free(pipex);
<<<<<<< HEAD
				system("leaks a.out");
								exit(1);
=======
				exit(1);
>>>>>>> 8f696a1a5d2ee8c03c8c69bac95cca889daedae3
			}
			// 	}else{
			// waitpid(pipex->pid, &st, 0);
		}
		pipex->index++;
	}
	while (wait(&st) != -1)
		pipex->status = WEXITSTATUS(st);
	free(pipex);
	while (1)
	{
		/* code */
	}
	
	return (0);
}



