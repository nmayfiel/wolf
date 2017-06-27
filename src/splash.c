/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splash.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 09:15:26 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/06/26 16:45:54 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "wolf.h"
#include <mlx.h>
#include <math.h>

#include <stdio.h>
/*
t_image		get_splash(void *mlx)
{
	t_image splash;

	splash.ptr = png_file_to_image(mlx, "assets/splash.png",
			&splash.width,
			&splash.height);
	splash.data = (int8_t *)mlx_get_data_addr(splash.ptr,
			&splash.bpp,
			&splash.size_line,
			&splash.endian);
	splash.center.x = splash.width / 2;
	splash.center.y = splash.height / 2;
	return (splash);
}
*/
t_image		get_splash_mask(void *mlx, int32_t width, int32_t height)
{
	t_image mask;

	mask.ptr = mlx_new_image(mlx,
			width,
			height);
	mask.width = width;
	mask.height = height;
	mask.data = (int8_t *)mlx_get_data_addr(mask.ptr,
			&mask.bpp,
			&mask.size_line,
			&mask.endian);
	mask.center.x = mask.width / 2;
	mask.center.y = mask.height / 2;
	clear_image(&mask, 0x00FFFFFF);
	return (mask);
}

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
