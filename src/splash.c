/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splash.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 09:15:26 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/05/14 21:32:23 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "fractol.h"
#include <mlx.h>
#include <math.h>

t_image		get_splash(void *mlx)
{
	t_image splash;

	splash.ptr = mlx_xpm_file_to_image(mlx, "assets/sprite.xpm",
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

void		render_splash(t_window *win)
{
	int32_t	*splash;
	size_t	i;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	i = 0;
	splash = (int32_t *)win->splash.data;
	while (i < win->splash.size_line / sizeof(int32_t) * win->splash.height)
	{
		if (splash[i] != 0)
		{
			r = (uint8_t)(i % win->splash.width);
			g = (uint8_t)(i / win->splash.width);
			b = (uint8_t)ABS((int)(sin(win->time) * 255));
			b = b > 0 ? b : 1;
			g = g > 0 ? g : 1;
			r = r > 0 ? r : 1;
			splash[i] = b | (g << 8) | (r << 16);
		}
		++i;
	}
	mlx_put_image_to_window(win->mlx, win->win, win->splash.ptr,
			win->center.x - win->splash.center.x,
			win->center.y - win->splash.center.y);
}
