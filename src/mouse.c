/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 21:16:08 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/06/14 01:47:58 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdio.h>

void		toggle_bool(int8_t *b)
{
	if (*b == 1)
		*b = 0;
	else
		*b = 1;
}
/*
1 is left click
2 is right click
5 is scroll up
6 is scroll down
*/
int32_t		mouse_hook(int button, int x, int y, t_window *win)
{
	t_mouse *mouse;

	mouse = &win->mouse;
	if (button == 1)
		mouse->click1 = 1;
	else if (button == 2)
		mouse->click2 = 1;
	mouse->location.x = ((double)x / (double)win->disp.width) - 0.5;
	mouse->location.y = ((double)y / (double)win->disp.height) - 0.5;
	win->mods.update = 1;
	return (0);
}

int32_t		mouse_moved(int x, int y, t_window *win)
{
	t_mouse *mouse;

	mouse = &win->mouse;
	mouse->location.x = ((double)x / (double)win->disp.width) - 0.5;
	mouse->location.y = ((double)y / (double)win->disp.height) - 0.5;
	win->mods.update = 1;
	return (0);
}
