/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:55:06 by aelomari          #+#    #+#             */
/*   Updated: 2024/02/20 22:17:54 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_cmddone(t_pipex *pipex, int x)
{
	pipex->j = 0;
	while (pipex->pathcmd[pipex->j])
	{
		if (access(pipex->pathcmd[pipex->j], X_OK) == 0 && x == 2)
		{
			pipex->cmd1 = ft_strdup(pipex->pathcmd[pipex->j]);
			break ;
		}
		if (access(pipex->pathcmd[pipex->j], X_OK) == 0 && x == 3)
		{
			pipex->cmd2 = ft_strdup(pipex->pathcmd[pipex->j]);
			break ;
		}
		pipex->j++;
	}
	if (x == 2 && !pipex->cmd1)
		ft_errorcmd(pipex);
	if (x == 3 && !pipex->cmd2)
		ft_errorcmd(pipex);
}

void	ft_checkcmd(t_pipex *pipex, int x)
{
	pipex->i = 0;
	while (!ft_strnstr(pipex->envs[pipex->i], "PATH=",
			ft_strlen(pipex->envs[pipex->i])) && pipex->envs[pipex->i])
		pipex->i++;
	pipex->path = ft_split(pipex->envs[pipex->i], '=');
	pipex->pathcmd = ft_split(pipex->path[1], ':');
	pipex->j = 0;
	while (pipex->pathcmd[pipex->j])
	{
		pipex->tmp = ft_strjoin(pipex->pathcmd[pipex->j], "/");
		pipex->tmp2 = ft_strjoin(pipex->tmp, pipex->avs[x]);
		free(pipex->pathcmd[pipex->j]);
		free(pipex->tmp);
		pipex->pathcmd[pipex->j] = pipex->tmp2;
		pipex->j++;
	}
	ft_cmddone(pipex, x);
	free_all(pipex->pathcmd);
	free_all(pipex->path);
}

void	checkallcmd(t_pipex *pipex)
{
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

int	main(int ac, char **av, char **env)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	pipexinit(ac, av, env, pipex);
	if (ac == 5)
	{
		checkallcmd(pipex);
		system("leaks  pipex");
	}
	else
		errorarg();
	system("leaks pipex");
	return (0);
}
