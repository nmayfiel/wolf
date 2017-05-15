/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 17:23:55 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/05/14 21:06:01 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <mlx.h>
#include <stdio.h>

static t_image	get_display_buffer(void *mlx, uint32_t width, uint32_t height)
{
	t_image display;

	display.width = width;
	display.height = height;
	display.ptr = mlx_new_image(mlx, width, height);
	display.data = (int8_t *)mlx_get_data_addr(display.ptr,
			&display.bpp,
			&display.size_line,
			&display.endian);
	display.size_in_bytes = width * height;
	display.center.x = width / 2;
	display.center.y = height / 2;
	return (display);
}

static void		init_window(t_window *win)
{
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	win->disp = get_display_buffer(win->mlx, WIN_WIDTH, WIN_HEIGHT);
	win->splash = get_splash(win->mlx);
	win->time = 0.0;
	win->center.x = (WIN_WIDTH / 2);
	win->center.y = (WIN_HEIGHT / 2);
	win->keys = 0;
	win->initialized = 0;
	win->mods = (t_mods){0.02, -0.7, 0.27015, 0, 0, 64, 0, 0};
	if (win->opts & OPT_GPU)
		create_cl_device(&win->cl, &win->opts);
}

static void		print_welcome_msg(int32_t gpu)
{
	ft_putendl("FRACT'OL: A 42 Graphics Project - by nmayfiel");
	if (gpu == 1)
		ft_putendl("OpenCL GPU 32 Bit Kernel");
	if (gpu == 2)
		ft_putendl("OpenCL GPU 64 Bit Kernel");
	ft_putendl("****************************************");
	ft_putendl("****** Controls ************************");
	ft_putendl("****** Arrow Keys:   Move Camera  ******");
	ft_putendl("****** W/S:          +/- Iter.    ******");
	ft_putendl("****** A/D:          Color/B&W    ******");
	ft_putendl("****** Mouse Wheel:  Zoom         ******");
	ft_putendl("****** ESC:          Quit         ******");
	ft_putendl("****************************************");
}

/*
** Rather than using key hook and mouse hook functions, I chose to use
** the generic mlx_hook function for assigning all event hooks
** You can find the values for event keys in minilibx/mlx_new_window.m
** int mlx_hook(void *win_ptr, int event, int mask, int (*f)(), void *param);
*/

int				main(int argc, char **argv)
{
	t_window	win;
	int32_t		gpu;

	if (argc == 1)
		print_usage(argv[0]);
	if (parse_options(argc - 1, argv + 1, &win) == -1)
		print_usage(argv[0]);
	init_window(&win);
	win.initialized = 1;
	gpu = 0;
	gpu += win.opts & OPT_GPU ? 1 : 0;
	gpu += win.opts & OPT_64 ? 1 : 0;
	print_welcome_msg(gpu);
	mlx_hook(win.win, 2, 0, remove_key, &win.keys);
	mlx_hook(win.win, 4, 0, mouse_hook, &win);
	mlx_hook(win.win, 6, 0, mouse_moved, &win);
	mlx_hook(win.win, 3, 0, add_key, &win.keys);
	mlx_hook(win.win, 17, 0, close_hook, &win);
	mlx_loop_hook(win.mlx, main_loop, &win);
	mlx_loop(win.mlx);
	return (0);
}
