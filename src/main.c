/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 17:23:55 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/06/26 17:13:35 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

int		expose_hook(t_window *win)
{
	if (win->game_state & GS_SPLASH)
		render_splash(win);
	else if (win->game_state & GS_TITLE)
		render_title(win);
	else
		render_game(win);
	return (0);
}

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
	display.size_in_pixels = width * height;
	display.size_in_bytes = display.size_line * height;
	display.center.x = width / 2;
	display.center.y = height / 2;
	return (display);
}

static t_image	get_texture(void *mlx, char *fn)
{
     t_image image;

     image.ptr = png_file_to_image(mlx, fn, &image.width, &image.height);
     image.data = (int8_t *)mlx_get_data_addr(image.ptr,
					      &image.bpp,
					      &image.size_line,
					      &image.endian);
     image.center.x = image.width / 2;
     image.center.y = image.height / 2;
     return (image);
}

static int32_t	**get_vertical_image_buffer_map(t_image *image)
{
     int32_t *buffer;
     int32_t **vertical_buffer;
     int i;
     int j;
     int k;

     buffer = (int32_t *)image->data;
     vertical_buffer = (int32_t **)malloc(sizeof(int32_t *) * image->size_in_pixels);
     i = 0;
     k = 0;
     while (i < image->width)
     {
	  j = 0;
	  while (j < image->height)
	  {
	       vertical_buffer[k] = &buffer[(image->width * j) + i];
	       ++j;
	       ++k;
	  }
	  ++i;
     }
     return (vertical_buffer);
}

static void		init_window(t_window *win)
{
	char *file_path;

	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	win->disp = get_display_buffer(win->mlx, WIN_WIDTH, WIN_HEIGHT);
	file_path = ft_strdup("assets/splash.png");
	win->splash = get_texture(win->mlx, file_path);
	free(file_path);
	win->splash_mask = get_splash_mask(win->mlx, win->splash.width, win->splash.height);
	win->time = 0.0;
	win->frame_time = 0.0;
	win->center.x = (WIN_WIDTH / 2);
	win->center.y = (WIN_HEIGHT / 2);
	win->keys = (t_keys){{0,0},{0,0},
			     {0,0},{0,0},
			     {0,0},{0,0},
			     {0,0},{0,0},
			     {0,0}};
	win->initialized = 0;
	win->mods = (t_mods){0, {64, 64}, 0, 0, 0, 0, 0};
	win->vertical_buffer = get_vertical_image_buffer_map(&win->disp);
	win->game_state = GS_SPLASH;
	file_path = ft_strdup("assets/title_texture.png");
	win->title_texture = get_texture(win->mlx, file_path);
	free(file_path);
	file_path = ft_strdup("assets/brick_wall.png");
	win->wall_texture = get_texture(win->mlx, file_path);
	free(file_path);
	file_path = ft_strdup("assets/cacodemon.png");
	win->enemy_texture = get_texture(win->mlx, file_path);
	free(file_path);
}

static void		print_welcome_msg(void)
{
	ft_putendl("WOLF 3D: A 42 Graphics Project - by nmayfiel");
	ft_putendl("****************************************");
	ft_putendl("****** Controls ************************");
	ft_putendl("****** W/S:          Move         ******");
	ft_putendl("****** A/D:          Strafe L/R   ******");
	ft_putendl("****** L/R Arrows:   Look L/R     ******");
	ft_putendl("****************************************");
	ft_putendl("****** ESC:          Quit         ******");
	ft_putendl("****************************************");
}

int				main(int argc, char **argv)
{
	t_window	win;
	
	sleep(10);
	if (argc != 1)
		print_usage(argv[0]);
	//if (parse_options(argc - 1, argv + 1, &win) == -1)
	//	print_usage(argv[0]);
	init_window(&win);
	if (read_level_map("assets/map.wolf", &win.level, &win.mods) != 1)
	     exit(0);
	win.initialized = 1;
	print_welcome_msg();
	mlx_hook(win.win, 2, 0, key_down, &win.keys);
	mlx_hook(win.win, 3, 0, key_up, &win.keys);
	mlx_hook(win.win, 12, 0, expose_hook, &win);
	mlx_hook(win.win, 17, 0, close_hook, &win);
	mlx_loop_hook(win.mlx, main_loop, &win);
	mlx_loop(win.mlx);
	return (0);
}
