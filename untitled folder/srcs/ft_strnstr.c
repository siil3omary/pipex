/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:15:19 by aelomari          #+#    #+#             */
/*   Updated: 2024/02/25 23:07:49 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_strnstr(const char *big, const char *little, size_t len )
{
	size_t	i;
	size_t	j;
    
if(big == NULL || little == NULL)
    return (NULL);
	i = 0;
	j = 0;
	if (*little == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (i + j < len && little[j] == big[i + j])
		{
			if (little[j + 1] == '\0')
			{
				return ((char *)big + i);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}
