/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:55:57 by aelomari          #+#    #+#             */
/*   Updated: 2024/02/20 18:14:41 by aelomari         ###   ########.fr       */
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
	pid_t	pid1;
	pid_t	pid2;
	int		infileFd;
	int		outfileFd;
	char	**envs;
	char	**path;
	char	**pathCmd;
    char **avs;
    int acs;
    char *tmp;
    char * tmp2;
    char *cmd;

}			t_pipex;

size_t		ft_strlen(const char *s);
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strdup(const char *s);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		**ft_split(char const *s, char c);
void		errorarg(void);
#endif