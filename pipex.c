/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:55:06 by aelomari          #+#    #+#             */
/*   Updated: 2024/02/18 21:43:24 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

int	main(int ac, char **av, char **env)
{
	int i = 0;
	(void)av;
    t_pipex pipex;
	if (ac == 5)
	{
		while (!ft_strnstr(env[i], "PATH=", ft_strlen(env[i])) && env[i])
		{
			i++;
		}
		pipex.path = ft_split(env[i], '=');
		pipex.pathCmd = ft_split(pipex.path[1], ':');
		int j = 0;
		while (pipex.pathCmd[j])
		{
			printf("%s\n", pipex.pathCmd[j]);
			j++;
		}

		free(pipex.path[0]);
	}
	else
	{
		ft_putstr_fd("\033[31mError: Bad arguments\n\e[0m", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <pathCmd1> <pathCmd2> <file2>\n", 1);
	}
	system("leaks pipex");
}