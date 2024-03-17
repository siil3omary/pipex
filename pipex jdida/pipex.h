/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 21:36:20 by aelomari          #+#    #+#             */
/*   Updated: 2024/03/16 08:58:47 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(PIPEX_H)
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct data
{
	int		*status;
	char	**path;
	int		infile_fd;
	int		outfile_fd;
	int		acs;
	char	**avs;
	char	**envs;
	int		pipe_fd[2];
	int		index;
	pid_t	pid;
	int		path_index;
	char	**cmd;

}			t_pipex;

void		*free_all(char **sp);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
char		*ft_strdup(const char *s);
size_t		ft_strlen(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char *s, char c);
void		second_cmd(t_pipex *pipex);
void		first_cmd(t_pipex *pipex);
void		ft_putstr_fd(char *str, int fd);
int			ft_strcmp(char *s1, char *s2);

#endif // PIPEX_H
