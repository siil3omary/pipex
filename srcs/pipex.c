/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:55:06 by aelomari          #+#    #+#             */
/*   Updated: 2024/02/21 19:33:07 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_checkfile(t_pipex *pipex)
{
	pipex->infile_fd = open(pipex->avs[1], O_RDONLY);
	pipex->outfile_fd = open(pipex->avs[4], O_CREAT, 00400, 00200, 00040,
			00004);
	if (pipex->infile_fd == -1)
		ft_errorfile(pipex);
	if (pipex->outfile_fd == -1)
		ft_errorfile(pipex);
}
void	ft_cmddone(t_pipex *pipex, int x)
{
	pipex->j = 0;
	while (pipex->pathcmd[pipex->j])
	{
		if (x == 2)
		{
			pipex->cmd1args = ft_split(pipex->pathcmd[pipex->j], ' ');
			if (access(pipex->cmd1args[0], X_OK) == 0 && x == 2)
			{
				pipex->cmd1 = ft_strdup(pipex->pathcmd[pipex->j]);
				// free_all(pipex->cmd1args);
				break ;
			}
        free_all(pipex->cmd1args);
		}
		if (x == 3)
		{
			pipex->cmd2args = ft_split(pipex->pathcmd[pipex->j], ' ');
			if (access(pipex->cmd2args[0], X_OK) == 0 && x == 3)
			{
				pipex->cmd2 = ft_strdup(pipex->pathcmd[pipex->j]);
				free_all(pipex->cmd2args);
				break ;
			}
            printf("cmd2args: %s\t %s \n", pipex->cmd2args[0] , pipex->cmd2args[1]);
        free_all(pipex->cmd2args);
		}
		pipex->j++;
	}
            printf("cmd1args: %s\t %s \n", pipex->cmd1args[0] , pipex->cmd1args[1]);
	if (x == 2 && !pipex->cmd1)
		ft_errorcmd(pipex, 2);
	if (x == 3 && !pipex->cmd2)
		ft_errorcmd(pipex, 3);

}

void	ft_checkcmd(t_pipex *pipex, int x)
{
	pipex->i = 0;
	while (!ft_strnstr(pipex->envs[pipex->i], "PATH=",
			ft_strlen(pipex->envs[pipex->i])) && pipex->envs[pipex->i])
		pipex->i++;
	pipex->path = ft_split(pipex->envs[pipex->i], '=');
	if (!pipex->path)
		return ;
	pipex->pathcmd = ft_split(pipex->path[1], ':');
	if (!pipex->pathcmd)
		return ;
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

int	main(int ac, char **av, char **env)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (0);
	pipexinit(ac, av, env, pipex);
	if (ac == 5)
	{
		checkall(pipex);
        printf("cmd1: %s\n", pipex->cmd1);
        printf("cmd1args: %s\t %s \t %s", pipex->cmd1args[0] , pipex->cmd1args[1], pipex->cmd1args[2]);
        execve(pipex->cmd1args[0], pipex->cmd1args, env);
	}
	else
		errorarg();
	return (0);
}
