/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 19:38:41 by aelomari          #+#    #+#             */
/*   Updated: 2024/04/22 15:29:35 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1)
		return (0);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] != s2[i])
		return (0);
	return (i);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (needle[j] == haystack[i + j] && i + j < len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)haystack + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

void	initstrct(t_pipex *pipex, int ac, char **av, char **env)
{
	pipex->acs = ac;
	pipex->avs = av;
	pipex->envs = env;
	pipex->infile_fd = 0;
	pipex->index = 2;
}

void	error_args(char **av)
{
	if (ft_strcmp(av[1], "--help"))
	{
		ft_putstr_fd("\033[32mUsage: \e[0m", 1);
		ft_putstr_fd("./pipex infile cmd1 cmd2 outfile\n", 1);
		exit(EXIT_FAILURE);
	}
	else
	{
		ft_putstr_fd("\033[31mpipex: \e[0m", 2);
		ft_putstr_fd("Bad argument", 2);
		ft_putstr_fd("\n\t --help for Usage\n", 2);
		exit(EXIT_FAILURE);
	}
}
