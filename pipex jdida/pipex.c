/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:10:30 by aelomari          #+#    #+#             */
/*   Updated: 2024/03/17 19:27:25 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_path(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->path[i])
	{
		free(pipex->path[i]);
		i++;
	}
	free(pipex->path);
}

void	get_path(t_pipex *pipex)
{
	int		i;
	char	*tmp;

	i = 0;
	while (pipex->envs[i])
	{
		if (ft_strnstr(pipex->envs[i], "PATH=", 5))
		{
			tmp = ft_strdup(pipex->envs[i] + 5);
			pipex->path = ft_split(tmp, ':');
			free(tmp);
			break ;
		}
		i++;
	}
}
char	**check_cmd(char *cmd, t_pipex *pipex)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	**result;

	i = 0;
	get_path(pipex);
	while (pipex->path[i])
	{
		tmp = ft_strjoin(pipex->path[i], "/");
		tmp2 = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(tmp2, X_OK) == 0)
		{
			result = ft_split(tmp2, ' ');
			free(tmp2);
			return (result);
		}
		free(tmp2);
		i++;
	}
	ft_putstr_fd("\033[31mpipex: \e[0m", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(":  ", 2);
	ft_putstr_fd("command not found\n", 2);
	return (NULL);
}

void	openfiles(t_pipex *pipex)
{
	pipex->infile_fd = open(pipex->avs[1], O_RDONLY);
	if (pipex->infile_fd == -1)
	{
		ft_putstr_fd("\033[31mpipex: \e[0m", 2);
		ft_putstr_fd(pipex->avs[1], 2);
		ft_putstr_fd(":  ", 2);
		perror("");
	}
	pipex->outfile_fd = open(pipex->avs[pipex->acs - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile_fd == -1)
	{
		ft_putstr_fd("\033[31mpipex: \e[0m", 2);
		ft_putstr_fd(pipex->avs[pipex->acs - 1], 2);
		ft_putstr_fd(":  ", 2);
		perror("");
	}
}

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

int	main(int ac, char **av, char **env)
{
	t_pipex	*pipex;

	if (ac < 5)
	{
		if (ft_strcmp(av[1], "--help"))
		{
			ft_putstr_fd("\033[32mUsage: \e[0m", 1);
			ft_putstr_fd("./pipex file1 cmd1 cmd2 file2", 1);
			exit(EXIT_FAILURE);
		}
		ft_putstr_fd("\033[31mpipex: \e[0m", 2);
		ft_putstr_fd("Bad argument", 2);
		ft_putstr_fd("\n\t --help for help\n", 2);
		exit(EXIT_FAILURE);
	}
	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	//  init args
	pipex->acs = ac;
	pipex->avs = av;
	pipex->envs = env;
	pipex->index = 0;
	pipex->infile_fd = 0;
	// pipex excute
	pipe(pipex->pipe_fd);
	while (pipex->index < ac - 3)
	{
		pipex->pid = fork();
		if (pipex->pid == -1)
		{
			ft_putstr_fd("\033[31mpipex: \e[0m", 2);
			ft_putstr_fd("fork failed", 2);
			exit(EXIT_FAILURE);
		}
		if (pipex->pid == 0)
		{
			if (pipex->index == 0)
			{
				openfiles(pipex);
				pipex->cmd = check_cmd(pipex->avs[pipex->index + 2], pipex);
				printf("cmd: %s\n", pipex->cmd[0]);
				free_path(pipex);
				free(pipex->cmd);
				// system("leaks a.out");
				exit(0);
			}
			else
			{
				pipex->cmd = check_cmd(pipex->avs[pipex->index + 2], pipex);
				printf("cmd: %s\n", pipex->cmd[0]);
				free_path(pipex);
				free(pipex->cmd);
				// system("leaks a.out");
				exit(0);
			}
		}
		else
			waitpid(pipex->pid, pipex->status, 0);
		pipex->index++;
	}
	return (0);
}
