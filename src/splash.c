/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splash.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 09:15:26 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/06/26 17:27:13 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "wolf.h"
#include <mlx.h>
#include <math.h>

#include <stdio.h>

void		render_splash(t_window *win)
{
	uint32_t	*splash;
	uint32_t	*mask;
	size_t	i;
	t_f2 uv;
	float time;
	
	i = 0;
	mlx_clear_window(win->mlx, win->win);
	clear_image(&win->disp, 0x00FFFFFF);
	clear_image(&win->splash_mask, 0x00FFFFFF);
	mlx_put_image_to_window(win->mlx, win->win, win->disp.ptr,
				win->center.x - win->disp.center.x,
				win->center.y - win->disp.center.y);
	if (win->time >= 2 && win->time < 5.5)
	{
		splash = (uint32_t *)win->splash.data;
		while (i < win->splash.size_line / sizeof(int32_t) * win->splash.height)
		{
			uv.x = (i % win->splash.width) / (float)win->splash.width;
			uv.y = (i / win->splash.width) / (float)win->splash.height;
			splash[i] = (uint8_t)ABS((int)(sin(win->time) * 255)) |
				((uint8_t)(uv.y * 255) << 8) |
				((uint8_t)(uv.x * 255) << 16) |
				(splash[i] & 0xFF000000);
			++i;
		}
		mlx_put_image_to_window(win->mlx, win->win, win->splash.ptr,
					win->center.x - win->splash.center.x,
					win->center.y - win->splash.center.y);
		i = 0;
		mask = (uint32_t *)win->splash_mask.data;
		time = win->time;
		if (win->time < 4.5)
		{
			time -= 2.0;
			if (time * 2.0 > 1.0)
				time = 1.0;
			else
				time *= 2.0;
		}
		else
		{
			time -= 4.5;
			if (time > 1.0)
				time = 0;
			else
				time = 1.0 - time;
		}
		while (i < win->splash_mask.size_line / sizeof(int32_t) * win->splash_mask.height)
		{
			mask[i] = 0x00FFFFFF | ((uint8_t)(time * 255) << 24);
			++i;
		}
		
		mlx_put_image_to_window(win->mlx, win->win, win->splash_mask.ptr,
					win->center.x - win->splash_mask.center.x,
					win->center.y - win->splash_mask.center.y);
	}
	else if (win->time >= 5.5)
	{
		win->game_state ^= GS_SPLASH;
		win->game_state |= GS_TITLE;		
	}
}
