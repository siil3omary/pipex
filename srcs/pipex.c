/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:55:06 by aelomari          #+#    #+#             */
/*   Updated: 2024/02/20 18:01:23 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"


int	main(int ac, char **av, char **env)
{
	int i = 0;
	(void)av;
	t_pipex pipex;
	pipex.envs = env;
	if (ac == 5)
	{
		while (!ft_strnstr(env[i], "PATH=", ft_strlen(env[i])) && env[i])
			i++;

		pipex.path = ft_split(env[i], '=');
		pipex.pathCmd = ft_split(pipex.path[1], ':');
		int j = 0;
		while (pipex.pathCmd[j])
		{
            pipex.tmp = ft_strjoin(pipex.pathCmd[j], "/");
            pipex.tmp2 = ft_strjoin(pipex.tmp, av[2]);
            free(pipex.pathCmd[j]);
            free(pipex.tmp);
            pipex.pathCmd[j] = pipex.tmp2;
            j++;
		}

        
        j = 0;
        while (pipex.pathCmd[j])
        {
            printf("%s\n", pipex.pathCmd[j]);
            j++;
        }
        
      
        

		free(pipex.path[0]);
		system("leaks  pipex");
	}
	else
	errorarg();
}