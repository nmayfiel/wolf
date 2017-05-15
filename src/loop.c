/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 21:01:02 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/05/14 21:01:11 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "fractol.h"
#include <stdlib.h>
#include <mlx.h>

int32_t			close_hook(t_window *win)
{
	mlx_destroy_window(win->mlx, win->win);
	if (win->opts & OPT_GPU)
		release_cl_device(&win->cl);
	exit(0);
}

void			limit_num(int32_t *n, int32_t low, int32_t high)
{
	if (*n > high)
		*n = high;
	if (*n < low)
		*n = low;
}

static int32_t	handle_keys(t_keys keys, t_mods *mods)
{
	if (keys & KVAL_UP)
		mods->yoffset += mods->scale * 11;
	if (keys & KVAL_DOWN)
		mods->yoffset -= mods->scale * 11;
	if (keys & KVAL_LEFT)
		mods->xoffset -= mods->scale * 11;
	if (keys & KVAL_RIGHT)
		mods->xoffset += mods->scale * 11;
	if (keys & KVAL_D)
		mods->color_index += 1;
	if (keys & KVAL_A)
		mods->color_index -= 1;
	limit_num(&mods->color_index, 0, 1);
	if (keys & KVAL_W)
		mods->iterations += 32;
	if (keys & KVAL_S)
		mods->iterations -= 32;
	limit_num(&mods->iterations, 0, 8192);
	return (keys != 0);
}

int32_t			main_loop(t_window *win)
{
	static int32_t	rendered_once = 0;
	int32_t			update;

	win->time += 0.01;
	if (win->keys & KVAL_ESC)
		close_hook(win);
	if (win->initialized == 1 && win->time >= 2.0)
	{
		update = handle_keys(win->keys, &win->mods);
		if (!rendered_once || update || win->mods.update)
			render(win);
		win->mods.update = 0;
		rendered_once = 1;
	}
	else
		render_splash(win);
	return (0);
}
