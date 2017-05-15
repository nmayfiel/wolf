/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 21:16:08 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/05/14 21:18:38 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int32_t		mouse_hook(int button, int x, int y, t_window *win)
{
	double	cx;
	double	cy;

	cx = win->disp.center.x;
	cy = win->disp.center.y;
	if (button == 4)
	{
		win->mods.xoffset -= win->mods.scale * ((double)x - cx) / 11;
		win->mods.yoffset += win->mods.scale * ((double)y - cy) / 11;
		win->mods.scale *= 1.1;
	}
	else if (button == 5)
	{
		win->mods.xoffset += win->mods.scale * ((double)x - cx) / 11;
		win->mods.yoffset -= win->mods.scale * ((double)y - cy) / 11;
		win->mods.scale /= 1.1;
	}
	win->mods.update = 1;
	return (0);
}

int32_t		mouse_moved(int x, int y, t_window *win)
{
	double cx;
	double cy;

	cx = win->disp.center.x;
	cy = win->disp.center.y;
	win->mods.xmouse = (x - (double)win->disp.center.x) / win->disp.width;
	win->mods.ymouse = (y - (double)win->disp.center.y) / win->disp.height;
	win->mods.update = 1;
	return (0);
}
