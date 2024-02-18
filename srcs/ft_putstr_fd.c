/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 23:01:32 by codespace         #+#    #+#             */
/*   Updated: 2024/02/17 22:17:45 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void ft_putstr_fd(char *s, int fd) {
    int i;

    if (s != NULL) {
        i = 0;
        while (s[i]) {
            ft_putchar_fd(s[i], fd);
            i++;
        }
    }
}
