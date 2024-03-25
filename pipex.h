/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 21:36:20 by aelomari          #+#    #+#             */
/*   Updated: 2024/03/25 02:35:08 by aelomari         ###   ########.fr       */
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
	int		status;
	int		infile_fd;
	int		outfile_fd;
	int		acs;
	int		path_index;
	int		pipe_fd[2];
	int		index;
	char	**avs;
	char	**envs;
	pid_t	pid;
	char	**cmd;

}			t_pipex;

void		initstrct(t_pipex *pipex, int ac, char **av, char **env);
void		ft_putstr_fd(char *str, int fd);
void		openfiles(t_pipex *pipex);
void		notcmd(char *cmd);
void		*free_all(char **sp);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strdup(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char *s, char c);
char		**check_cmd(char *cmd, t_pipex *pipex);
int			ft_strcmp(char *s1, char *s2);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlen(const char *s);
void		ft_pipex(t_pipex *pipex);
void		fork_error(void);
void		last_child(t_pipex *pipex);
void		secend_child(t_pipex *pipex);
void		first_child(t_pipex *pipex);
void		error_args(char **av);

#endif // PIPEX_H
