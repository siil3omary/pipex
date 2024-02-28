/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:55:57 by aelomari          #+#    #+#             */
/*   Updated: 2024/02/28 17:35:17 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <unistd.h>
#include <sys/wait.h>

typedef struct s_pipex
{
    int infile_fd;
    int outfile_fd;
    int acs;
    char **avs;
    char **envs;
    int prev_fd;
    int next_fd;
    int status;  
    pid_t   pid[32768];
    int pipe_fd[2];
    int i;
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