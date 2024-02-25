/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 14:41:30 by aelomari          #+#    #+#             */
/*   Updated: 2024/02/25 23:08:03 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_checkfile(t_pipex *pipex)
{
	pipex->infile_fd = open(pipex->avs[1], O_RDONLY);
	pipex->outfile_fd = open(pipex->avs[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->infile_fd == -1)
		ft_errorfile(pipex);
	if (pipex->outfile_fd == -1)
		ft_errorfile(pipex);
}

int	set1(t_pipex *pipex)
{
	pipex->cmd1args = ft_split(pipex->pathcmd[pipex->j], ' ');
	if (access(pipex->cmd1args[0], X_OK) == 0)
	{
		pipex->cmd1 = ft_strdup(pipex->cmd1args[0]);
		return (1);
	}
	free_all(pipex->cmd1args);
	return (0);
}

int	set2(t_pipex *pipex)
{
	pipex->cmd2args = ft_split(pipex->pathcmd[pipex->j], ' ');
	if (access(pipex->cmd2args[0], X_OK) == 0)
	{
		pipex->cmd2 = ft_strdup(pipex->cmd2args[0]);
		return (1);
	}
	free_all(pipex->cmd2args);
	return (0);
}

void	ft_cmddone(t_pipex *pipex, int x)
{
	pipex->j = 0;
	while (pipex->pathcmd[pipex->j])
	{
		if (x == 2 && set1(pipex))
			break ;
		if (x == 3 && set2(pipex))
			break ;
		pipex->j++;
	}
	free_all(pipex->pathcmd);
	if (x == 2 && !pipex->cmd1)
		ft_errorcmd(pipex, 2);
	if (x == 3 && !pipex->cmd2)
		ft_errorcmd(pipex, 3);
}

void	ft_checkcmd(t_pipex *pipex, int x)
{
	pipex->i = 0;
	while (!ft_strnstr(pipex->envs[pipex->i], "PATH=",
			6) && pipex->envs[pipex->i])
		pipex->i++;
                if (!pipex->envs[pipex->i])
                ft_errorcmd(pipex, x);

        
	pipex->path = ft_split(pipex->envs[pipex->i], '=');
	if (!pipex->path)
		return ;
	pipex->pathcmd = ft_split(pipex->path[1], ':');
	free_all(pipex->path);
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
}


