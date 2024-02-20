/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:55:57 by aelomari          #+#    #+#             */
/*   Updated: 2024/02/20 22:16:27 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		i;
	int		j;
	pid_t	pid1;
	pid_t	pid2;
	int		infile_fd;
	int		outfile_fd;
	char	**envs;
	char	**path;
	char	**pathcmd;
	char	**avs;
	int		acs;
	char	*tmp;
	char	*tmp2;
	char	*cmd1;
	char	*cmd2;

}			t_pipex;

void		ft_errorcmd(t_pipex *pipex);
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
void		*free_all(char **sp);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strdup(const char *s);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		**ft_split(char const *s, char c);
void		errorarg(void);
#endif