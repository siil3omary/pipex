/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:55:57 by aelomari          #+#    #+#             */
/*   Updated: 2024/02/28 18:16:33 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <unistd.h>
#include <sys/wait.h>

typedef struct s_pipex
{
	int		pip[2];
	int		status;
	pid_t	pid;
	int		i;
	int		j;
	int		acs;
	int		infile_fd;
	int		outfile_fd;
	char	*tmp;
	char	*tmp2;
	char	*cmd1;
	char	*cmd2;
	char	**avs;
	char	**envs;
	char	**path;
	char	**pathcmd;
	char	**cmd1args;
	char	**cmd2args;

}			t_pipex;

    void		ft_checkfile(t_pipex *pipex);
void		child_process(t_pipex *pipex);
void		child1_process(t_pipex *pipex);
void		ft_cmddone(t_pipex *pipex, int x);
void		ft_checkcmd(t_pipex *pipex, int x);
void		checkall(t_pipex *pipex);
void		pipexinit(int ac, char **av, char **env, t_pipex *pipex);
void		ft_errorfile(t_pipex *pipex);
void		errorarg(void);
void		ft_errorcmd(t_pipex *pipex, int x);
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
void		*free_all(char **sp);
char		*ft_strdup(const char *s);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strnstr(const char *big, const char *little, size_t len);
#endif