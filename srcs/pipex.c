/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.>c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:55:06 by aelomari          #+#    #+#             */
/*   Updated: 2024/02/20 18:10:48 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	cmdDone(t_pipex *pipex, int x)
{
	pipex->j = 0;
	while (pipex->pathCmd[pipex->j])
	{
		if (access(pipex->pathCmd[pipex->j], X_OK) == 0 && x == 2)
		{
			pipex->cmd1 = ft_strdup(pipex->pathCmd[pipex->j]);
			break ;
		}
		if (access(pipex->pathCmd[pipex->j], X_OK) == 0 && x == 3)
		{
			pipex->cmd2 = ft_strdup(pipex->pathCmd[pipex->j]);
			break ;
		}
		pipex->j++;
	}
	if (x == 2 && !pipex->cmd1)
		errorCmd(pipex->avs[x]);
	if (x == 3 && !pipex->cmd2)
		errorCmd(pipex->avs[x]);
}
void	checkCmd(t_pipex *pipex, int x)
{
	pipex->i = 0;
	while (!ft_strnstr(pipex->envs[pipex->i], "PATH=",
			ft_strlen(pipex->envs[pipex->i])) && pipex->envs[pipex->i])
		pipex->i++;
	pipex->path = ft_split(pipex->envs[pipex->i], '=');
	pipex->pathCmd = ft_split(pipex->path[1], ':');
	pipex->j = 0;
	while (pipex->pathCmd[pipex->j])
	{
		pipex->tmp = ft_strjoin(pipex->pathCmd[pipex->j], "/");
		pipex->tmp2 = ft_strjoin(pipex->tmp, pipex->avs[x]);
		free(pipex->pathCmd[pipex->j]);
		free(pipex->tmp);
		pipex->pathCmd[pipex->j] = pipex->tmp2;
		pipex->j++;
	}
	cmdDone(pipex, x);
	free_all(pipex->pathCmd);
	free_all(pipex->path);
}

int	main(int ac, char **av, char **env)
{
	t_pipex *pipex = malloc(sizeof(t_pipex));
	pipex->avs = av;
	pipex->acs = ac;
	pipex->envs = env;
	if (ac == 5)
	{
		checkCmd(pipex, 2);
		checkCmd(pipex, 3);
		printf("cmd: %s\n", pipex->cmd1);
		printf("cmd: %s\n", pipex->cmd2);

		system("leaks  pipex");
	}
	else
		errorarg();
}