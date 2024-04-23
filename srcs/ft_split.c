/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:51:30 by aelomari          #+#    #+#             */
/*   Updated: 2024/04/23 12:42:14 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	word_count(const char *str, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] != c) && ((str[i + 1] == c) || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

void	*free_all(char **sp)
{
	size_t	j;

	j = 0;
	// if (!sp || !sp[j])
	// {
	// 	return (NULL);
	// }
	while (sp[j])
	{
		free(sp[j]);
		j++;
	}
	free(sp);
	return (NULL);
}
static void	fill_split(char **split, char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	wordlen;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			wordlen = 0;
			while (s[i + wordlen] && s[i + wordlen] != c)
				wordlen++;
			split[j] = malloc(wordlen + 1);
			if (!split[j])
				free_all(split);
			ft_strlcpy(split[j], s + i, wordlen + 1);
			i += wordlen;
			j++;
		}
	}
	split[j] = NULL;
}

char	**ft_split(char *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = malloc((word_count(s, c) + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	fill_split(split, s, c);
	return (split);
}
