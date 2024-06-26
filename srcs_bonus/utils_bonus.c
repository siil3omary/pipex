/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:06:31 by aelomari          #+#    #+#             */
/*   Updated: 2024/04/20 20:15:18 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**check_excut(char *cmd)
{
	char	**result;

	result = ft_split(cmd, ' ');
	if (access(result[0], F_OK | X_OK) == 0)
		return (result);
	free_all(result);
	return (NULL);
}

char	**get_path(t_pipex *pipex)
{
	int		i;
	char	**path;

	path = NULL;
	if (pipex->envs == NULL)
		return (free(pipex), NULL);
	i = 0;
	while (pipex->envs[i])
	{
		if (ft_strnstr(pipex->envs[i], "PATH=", 5))
		{
			path = ft_split(pipex->envs[i] + 5, ':');
			return (path);
		}
		i++;
	}
	return (free_all(path), free(pipex), NULL);
}

void	notcmd(char *cmd)
{
	ft_putstr_fd("\033[31mpipex: \e[0m", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(":  ", 2);
	ft_putstr_fd("command not found\n", 2);
}

char	**check_cmd(char *cmd, t_pipex *pipex)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	**path;
	char	**result;

	i = 0;
	result = check_excut(cmd);
	if (result)
		return (result);
	path = get_path(pipex);
	if (!path)
		return (notcmd(cmd), NULL);
	while (path[i])
	{
		tmp = ft_strjoin(path[i++], "/");
		tmp2 = ft_strjoin(tmp, cmd);
		free(tmp);
		result = ft_split(tmp2, ' ');
		free(tmp2);
		if (access(result[0], X_OK) == 0)
			return (free_all(path), result);
		free_all(result);
	}
	return (notcmd(cmd), free_all(path), NULL);
}

void	openfiles(t_pipex *pipex)
{
	pipex->infile_fd = open(pipex->avs[1], O_RDONLY);
	if (pipex->infile_fd == -1)
	{
		error_file(pipex->avs[1]);
		perror("");
		if ((access(pipex->avs[1], F_OK) == 0) && (access(pipex->avs[1],
					R_OK) == -1))
			exit(0);
	}
	pipex->outfile_fd = open(pipex->avs[pipex->acs - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile_fd == -1)
	{
		error_file(pipex->avs[pipex->acs - 1]);
		perror("");
	}
}
