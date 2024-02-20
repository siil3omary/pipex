/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:46:31 by aelomari          #+#    #+#             */
/*   Updated: 2024/02/20 22:16:11 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_errorcmd(t_pipex *pipex)
{
	if (pipex->cmd1 == NULL)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(pipex->avs[2], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(pipex->avs[3], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	system("leaks  pipex");
	exit(127);
}

void	errorarg(void)
{
	ft_putstr_fd("\033[31mError: Bad arguments\n\e[0m", 2);
	ft_putstr_fd("Ex: ./pipex <file1> <pathCmd1> <pathCmd2> <file2>\n", 1);
	system("leaks  pipex");
}
