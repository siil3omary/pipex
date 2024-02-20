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

void	checkCmd(t_pipex *pipex)
{
	int	i;
	int	j;

	i = 0;
	while (!ft_strnstr(pipex->envs[i], "PATH=", ft_strlen(pipex->envs[i]))
		&& pipex->envs[i])
		i++;
	pipex->path = ft_split(pipex->envs[i], '=');
	pipex->pathCmd = ft_split(pipex->path[1], ':');
	j = 0;
	while (pipex->pathCmd[j])
	{
		pipex->tmp = ft_strjoin(pipex->pathCmd[j], "/");
		pipex->tmp2 = ft_strjoin(pipex->tmp, pipex->avs[2]);
		free(pipex->pathCmd[j]);
		free(pipex->tmp);
		pipex->pathCmd[j] = pipex->tmp2;
		j++;
	}
	j = 0;
	while (pipex->pathCmd[j])
	{
		if (access(pipex->pathCmd[j], F_OK) == 0)
			pipex->cmd = pipex->pathCmd[j];
		j++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipex *pipex;
	pipex->avs = av;
	pipex->acs = ac;
	pipex->envs = env;
	if (ac == 5)
	{

        checkCmd(pipex);
		printf("cmd: %s\n", pipex->cmd);

		system("leaks  pipex");
	}
	else
		errorarg();
}