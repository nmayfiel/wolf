/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 08:44:49 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/05/09 02:01:03 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "fractol.h"
#include <mlx.h>
#include <math.h>

void clear_image(t_window *win, int32_t color)
{
	int32_t i;

	i = 0;
	while (i < win->disp.size_in_bytes * 4)
	{
		win->disp.data[i] = color;
		i++;
	}
}
