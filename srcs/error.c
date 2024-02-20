/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:46:31 by aelomari          #+#    #+#             */
/*   Updated: 2024/02/20 17:46:49 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	errorarg(void)
{
	ft_putstr_fd("\033[31mError: Bad arguments\n\e[0m", 2);
	ft_putstr_fd("Ex: ./pipex <file1> <pathCmd1> <pathCmd2> <file2>\n", 1);
}