/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelomari <aelomari@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:42:01 by aelomari          #+#    #+#             */
/*   Updated: 2024/03/18 22:13:55 by aelomari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;
if(s == NULL)
    return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}
import pygame
import caffeine
import subprocess
from datetime import datetime, timedelta
import os

#Configuration constants
#CONF_background_image = "../Downloads/kamikaze-4579163.jpeg"
CONF_background_image = "b.jpg"
CONF_width, CONF_height = 5120, 2880
CONF_window_flags = pygame.FULLSCREEN|pygame.NOFRAME|pygame.HWSURFACE
CONF_exit_passwd = "walid"
CONF_hotkey_timeout = 100
CONF_network_check_delay = 60 * 5
CONF_max_stay_time = 60608

start_time = datetime.now()
pygame.init()
screen = pygame.display.set_mode((CONF_width, CONF_height), flags=CONF_window_flags)
running = True
#loading background image
window_size = pygame.display.get_window_size()
background_image = pygame.image.load(CONF_background_image)
background_image = pygame.transform.scale(background_image, window_size)
hotkey_buffer = ""
hotkey_iter = 0
network_iter = 0
###caffeine.on()
counter = 0
while running:
    pygame.mouse.set_system_cursor(pygame.SYSTEM_CURSOR_NO)
    pygame.mouse.set_visible(0)
    for event in pygame.event.get():
        if event.type == 2501:
            os.system("pmset displaysleepnow")
        if event.type == pygame.KEYDOWN:
            if event.key > 0 and event.key < 255:
                hotkey_buffer += chr(event.key)
                hotkey_iter = CONF_hotkey_timeout
        #if hotkey_buffer == CONF_exit_passwd:
        #    running = False
        if CONF_exit_passwd in hotkey_buffer:
            running = False
    screen.blit(background_image, [0, 0])
    #if network_iter >= CONF_network_check_delay:
    #    res = subprocess.check_output(["curl", "https://kerneloverseer.github.io/static/lock.bool%22])
    #    res = res.decode()
    #    if "true" in res:
    #        exit(1)
    #    network_iter = 0
    if hotkey_iter <= 0 and hotkey_buffer:
        hotkey_buffer = ""
    network_iter += 1
    hotkey_iter -= 1
    pygame.display.flip()
    time_now = datetime.now()
    if start_time + timedelta(seconds=CONF_max_stay_time) < time_now:
        exit(1)