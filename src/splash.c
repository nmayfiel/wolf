/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splash.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 09:15:26 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/08/02 02:48:55 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "wolf.h"
#include <mlx.h>
#include <math.h>

void		display_splash(t_window *win)
{
	uint32_t i;
	uint32_t *splash;
	t_f2 uv;
	float time;

	time = win->clock.time;
	splash = (uint32_t *)win->assets.splash.data;
	i = 0;
	while (i < win->assets.splash.size_line / sizeof(int32_t) * win->assets.splash.height)
	{
		uv.x = (i % win->assets.splash.width) / (float)win->assets.splash.width;
		uv.y = (i / win->assets.splash.width) / (float)win->assets.splash.height;
		splash[i] = (uint8_t)ABS((int)(sin(time) * 255)) |
			((uint8_t)(uv.y * 255) << 8) |
			((uint8_t)(uv.x * 255) << 16) |
			(splash[i] & 0xFF000000);
		++i;
	}
	mlx_put_image_to_window(win->mlx, win->win, win->assets.splash.ptr,
				win->center.x - win->assets.splash.center.x,
				win->center.y - win->assets.splash.center.y);
}

float		splash_one(float time)
{
	time -= 1.0;
	if (time * 2.0 > 1.0)
		time = 1.0;
	else
		time *= 2.0;
	return (time);
}

float		splash_two(float time)
{
	time -= 4.5;
	if (time > 1.0)
		time = 0;
	else
		time = 1.0 - time;
	return (time);
}

void		display_splash_mask(t_window *win)
{
	uint32_t i;
	uint32_t *mask;
	float	time;

	i = 0;
	time = win->clock.time;
	mask = (uint32_t *)win->assets.splash_mask.data;
	time = time < 4.5 ? splash_one(time) : splash_two(time);
	while (i < win->assets.splash_mask.size_line / sizeof(int32_t) * win->assets.splash_mask.height)
	{
		mask[i] = 0x00FFFFFF | ((uint8_t)(time * 255) << 24);
		++i;
	}
	mlx_put_image_to_window(win->mlx, win->win, win->assets.splash_mask.ptr,
				win->center.x - win->assets.splash_mask.center.x,
				win->center.y - win->assets.splash_mask.center.y);
}

void		render_splash(t_window *win)
{
	float		time;

	mlx_clear_window(win->mlx, win->win);
	clear_image(&win->assets.display_buffer, 0x00FFFFFF);
	clear_image(&win->assets.splash_mask, 0x00FFFFFF);
	mlx_put_image_to_window(win->mlx, win->win, win->assets.display_buffer.ptr,
				win->center.x - win->assets.display_buffer.center.x,
				win->center.y - win->assets.display_buffer.center.y);
	time = win->clock.time;
	if (time >= 1 && time < 5.5)
	{
		display_splash(win);
		display_splash_mask(win);
	}
	else if (time >= 5.5)
	{
		win->game_state ^= GS_SPLASH;
		win->game_state |= GS_TITLE;		
	}
}
