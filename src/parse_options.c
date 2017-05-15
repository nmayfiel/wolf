/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 21:13:25 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/05/14 21:14:03 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		parse_options(int num_opts, char **opts, t_window *win)
{
	int		i;

	win->opts = 0;
	if (ft_strequ(opts[0], "julia"))
		win->opts |= OPT_JULIA;
	else if (ft_strequ(opts[0], "mandelbrot"))
		win->opts |= OPT_MANDELBROT;
	else if (ft_strequ(opts[0], "ship"))
		win->opts |= OPT_SHIP;
	else
		return (-1);
	i = 1;
	while (i < num_opts)
	{
		if (ft_strequ(opts[i], "-gpu32"))
			win->opts |= OPT_GPU;
		else if (ft_strequ(opts[i], "-gpu64"))
			win->opts |= OPT_GPU | OPT_64;
		else
			return (-1);
		++i;
	}
	return (1);
}
