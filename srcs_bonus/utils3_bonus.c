/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 23:35:09 by aelomari          #+#    #+#             */
/*   Updated: 2024/03/26 23:45:06 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_file(char *str)
{
	ft_putstr_fd("\033[31mpipex: \e[0m", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(":  ", 2);
}
