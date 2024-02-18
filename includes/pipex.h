/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:55:57 by aelomari          #+#    #+#             */
/*   Updated: 2024/02/18 21:26:34 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <strings.h>

size_t ft_strlen(const char *s);
void ft_putstr_fd(char *s, int fd);
void ft_putchar_fd(char c, int fd);
size_t ft_strlcpy(char *dest, const char *src, size_t size);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_strdup(const char *s);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	**ft_split(char const *s, char c);
#endif