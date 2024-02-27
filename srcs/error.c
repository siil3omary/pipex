/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:46:31 by aelomari          #+#    #+#             */
/*   Updated: 2024/02/27 18:43:56 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_errorcmd(t_pipex *pipex, int x)
{
	if (x == 2)
	{
		ft_putstr_fd("\033[31mpipex: \e[0m", 2);
		ft_putstr_fd("command not found : ", 2);
		ft_putstr_fd(pipex->avs[2], 2);
		ft_putchar_fd('\n', 2);
		ft_checkcmd(pipex, 3);
	    exit(0);
        
	}
	else
	{
		ft_putstr_fd("\033[31mpipex: \e[0m", 2);
		ft_putstr_fd("command not found : ", 2);
		ft_putstr_fd(pipex->avs[3], 2);
		ft_putchar_fd('\n', 2);
	}
	exit(127);
}

void	ft_errorfile(t_pipex *pipex)
{
	if (pipex->infile_fd == -1)
	{
		ft_putstr_fd("\033[31mpipex: \e[0m", 2);
		ft_putstr_fd(": No such file or directory : ", 2);
		ft_putstr_fd(pipex->avs[1], 2);
		ft_putchar_fd('\n', 2);
		ft_checkcmd(pipex, 3);
        free(pipex->cmd2);
		ft_checkcmd(pipex, 2);
	}
	exit(0);
}

void	errorarg(void)
{
	ft_putstr_fd("\033[31mError: Bad arguments\n\e[0m", 2);
	ft_putstr_fd("Ex: ./pipex <file1> <pathCmd1> <pathCmd2> <file2>\n", 1);
	system("leaks  pipex");
}
