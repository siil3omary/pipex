/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:55:06 by aelomari          #+#    #+#             */
/*   Updated: 2024/02/22 16:41:44 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_checkfile(t_pipex *pipex)
{
	pipex->infile_fd = open(pipex->avs[1], O_RDONLY);
	pipex->outfile_fd = open(pipex->avs[4], O_CREAT | O_RDWR , 0644);
	if (pipex->infile_fd == -1)
		ft_errorfile(pipex);
	if (pipex->outfile_fd == -1)
		ft_errorfile(pipex);
}

int	set1(t_pipex *pipex)
{
	pipex->cmd1args = ft_split(pipex->pathcmd[pipex->j], ' ');
	if (access(pipex->cmd1args[0], X_OK) == 0)
	{
		pipex->cmd1 = ft_strdup(pipex->cmd1args[0]);
		return (1);
	}
	free_all(pipex->cmd1args);
	return (0);
}

int	set2(t_pipex *pipex)
{
	pipex->cmd2args = ft_split(pipex->pathcmd[pipex->j], ' ');
	if (access(pipex->cmd2args[0], X_OK) == 0)
	{
		pipex->cmd2 = ft_strdup(pipex->cmd2args[0]);
		return (1);
	}
	free_all(pipex->cmd2args);
	return (0);
}

void	ft_cmddone(t_pipex *pipex, int x)
{
	pipex->j = 0;
	while (pipex->pathcmd[pipex->j])
	{
		if (x == 2 && set1(pipex))
			break ;
		if (x == 3 && set2(pipex))
			break ;
		pipex->j++;
	}
	free_all(pipex->pathcmd);
	if (x == 2 && !pipex->cmd1)
		ft_errorcmd(pipex, 2);
	if (x == 3 && !pipex->cmd2)
		ft_errorcmd(pipex, 3);
}

void	ft_checkcmd(t_pipex *pipex, int x)
{
	pipex->i = 0;
	while (!ft_strnstr(pipex->envs[pipex->i], "PATH=",
			ft_strlen(pipex->envs[pipex->i])) && pipex->envs[pipex->i])
		pipex->i++;
	pipex->path = ft_split(pipex->envs[pipex->i], '=');
	if (!pipex->path)
		return ;
	pipex->pathcmd = ft_split(pipex->path[1], ':');
	free_all(pipex->path);
	pipex->j = 0;
	while (pipex->pathcmd[pipex->j])
	{
		pipex->tmp = ft_strjoin(pipex->pathcmd[pipex->j], "/");
		pipex->tmp2 = ft_strjoin(pipex->tmp, pipex->avs[x]);
		free(pipex->pathcmd[pipex->j]);
		free(pipex->tmp);
		pipex->pathcmd[pipex->j] = pipex->tmp2;
		pipex->j++;
	}
	ft_cmddone(pipex, x);
}

void	checkall(t_pipex *pipex)
{
	ft_checkfile(pipex);
	ft_checkcmd(pipex, 2);
	ft_checkcmd(pipex, 3);
}

void	pipexinit(int ac, char **av, char **env, t_pipex *pipex)
{
	pipex->acs = ac;
	pipex->avs = av;
	pipex->envs = env;
	pipex->cmd1 = NULL;
	pipex->cmd2 = NULL;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// int main(void) {
//     int status;
//     pid_t pid = fork();

//     if (pid < 0) {
//         // Fork failed
//         perror("fork");
//         exit(EXIT_FAILURE);
//     } else if (pid == 0) {
//         // Child process
//         waitpid(pid, &status, 0);
//         printf("hello\n");
//     system("leaks pipex");
//         exit(EXIT_SUCCESS);
//     } else {
//         // Parent process
//         waitpid(pid, &status, 0);
//         if (WIFEXITED(status)) {
//             printf("Child process exited with status %d\n", WEXITSTATUS(status));
//         } else {
//             printf("Child process did not exit normally\n");
//         }
//         printf("world\n");
//     system("leaks pipex");
        
//     }

//     // Execute "leaks pipex" command

//     return 0;
// }
int main(int ac, char **av, char **env)
{
	if (ac == 5)
	{
	t_pipex	*pipex;
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (0);
	pipexinit(ac, av, env, pipex);
		checkall(pipex);

		system("leaks pipex");
	}
	else
		errorarg();

	return (0);
    
}
// }0
