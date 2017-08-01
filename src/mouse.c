/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 21:16:08 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/08/01 02:26:37 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdio.h>

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
	mouse->location.x = x;
	mouse->location.y = y;
	win->mods.update = 1;
	return (0);
}

int32_t		mouse_moved(int x, int y, t_window *win)
{
	t_mouse *mouse;
	//t_double2 previous_location;

	// Need to get the mouse diff x in order to see which direction we should push the rotation of the player.

	mouse = &win->mouse;
	mouse->diff.x = x;
	mouse->diff.y = y;
//	mouse->location.x = ((double)x / (double)win->disp.width) - 0.5;
	//mouse->diff.x = mouse->location.x -  previous_location.x;
//	mouse->location.y = ((double)y / (double)win->disp.height) - 0.5;
	//mouse->diff.y = mouse->location.y -  previous_location.y;
	win->mods.update = 1;
	return (0);
}
