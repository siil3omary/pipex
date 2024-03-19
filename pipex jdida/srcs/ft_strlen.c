/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:42:01 by aelomari          #+#    #+#             */
<<<<<<< HEAD:pipex jdida/srcs/ft_strlen.c
/*   Updated: 2024/03/19 20:40:14 by aelomari         ###   ########.fr       */
=======
/*   Updated: 2024/03/19 00:29:53 by aelomari         ###   ########.fr       */
>>>>>>> 8f696a1a5d2ee8c03c8c69bac95cca889daedae3:pipex jdida/ft_strlen.c
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (s == NULL)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}
