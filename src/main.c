/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 17:23:55 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/06/30 00:14:03 by nmayfiel         ###   ########.fr       */
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

t_image get_image_of_size(void *mlx, uint32_t width, uint32_t height)
{
	t_image image;

	image.width = width;
	image.height = height;
	image.ptr = mlx_new_image(mlx, width, height);
	image.data = (int8_t *)mlx_get_data_addr(image.ptr,
						 &image.bpp,
						 &image.size_line,
						 &image.endian);
	image.size_in_pixels = width * height;
	image.size_in_bytes = image.size_line * height;
	image.center.x = width / 2;
	image.center.y = height / 2;
	return (image);
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
     image.size_in_pixels = image.width * image.height;
     image.size_in_bytes = image.size_line * image.height;
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

t_tx_sample enemies[34];

void    setup_enemies()
{
	enemies[0] = (t_tx_sample){308, 11, 1, 1, 67, 67};
	enemies[1] = (t_tx_sample){236, 12, 1, 1, 67, 67};
	enemies[2] = (t_tx_sample){159, 9, 1, 1, 67, 67};
	enemies[3] = (t_tx_sample){91, 11, 1, 1, 67, 67};
	enemies[4] = (t_tx_sample){18, 12, 1, 1, 67, 67};
	enemies[5] = (t_tx_sample){91, 11, -1, 1, 67, 67};
	enemies[6] = (t_tx_sample){159, 9, -1, 1, 67, 67};
	enemies[7] = (t_tx_sample){236, 12, -1, 1, 67, 67};
	int i = 8;
	while (i < 34)
	{
		enemies[i] = (t_tx_sample){0, 0, 1, 1, 67, 67};
		++i;
	}
}

//t_tx_sample shotguns[11];

void setup_shotgun_sample(t_gun *gun)
{
	gun->sample_data[0] = (t_tx_sample){26, 0, 1, 1, 70, 96};
        gun->sample_data[1] = (t_tx_sample){106, 0, 1, 1, 70, 96};
	gun->sample_data[2] = (t_tx_sample){182, 0, 1, 1, 70, 96};
        gun->sample_data[3] = (t_tx_sample){256, 0, 1, 1, 70, 96};
	int i = 4;
	while (i < 11)
	{
		gun->sample_data[i] = (t_tx_sample){0, 0, 1, 1, 96, 96};
		++i;
	}
	gun->default_anim = 1;
	gun->default_anim_start_frame = 0;
	gun->default_anim_end_frame = 0;
	gun->default_time_per_frame = 0;
	gun->default_start_time = 0;
	gun->shooting_anim = 0;
	gun->shooting_anim_time = 0;
	gun->shooting_anim_time_per_frame = 0.08;
	gun->shooting_anim_frame_start = 0;
	gun->shooting_anim_frame_end = 3;
}

static void		init_window(t_window *win)
{
	char *file_path;

	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	win->disp = get_image_of_size(win->mlx, WIN_WIDTH, WIN_HEIGHT);
	file_path = ft_strdup("assets/splash.png");
	win->splash = get_texture(win->mlx, file_path);
	free(file_path);
	win->splash_mask = get_image_of_size(win->mlx, WIN_WIDTH, WIN_HEIGHT);
	clear_image(&win->splash_mask, 0x00FFFFFF);
	win->time = 0.0;
	win->frame_time = 0.0;
	win->center.x = (WIN_WIDTH / 2);
	win->center.y = (WIN_HEIGHT / 2);
	win->keys = (t_keys){{0,0},{0,0},
			     {0,0},{0,0},
			     {0,0},{0,0},
			     {0,0},{0,0},
			     {0,0},{0,0},{0,0},{0,0}};
	win->initialized = 0;
	win->mods = (t_mods){0, {612, 612}, 0, 0, 0, 0, 0, 1.0, 0, 0, 0, 0, {0, {612, 612}, 0, 0, 0, 0}};
	win->vertical_buffer = get_vertical_image_buffer_map(&win->disp);
	win->game_state = GS_SPLASH;
	win->minimap = get_image_of_size(win->mlx, 200, 150);
	file_path = ft_strdup("assets/title_texture.png");
	win->title_texture = get_texture(win->mlx, file_path);
	free(file_path);
	file_path = ft_strdup("assets/brick_wall.png");
	win->wall_texture = get_texture(win->mlx, file_path);
	free(file_path);
	file_path = ft_strdup("assets/cacodemon.png");
	win->enemy_texture = get_texture(win->mlx, file_path);
	free(file_path);
	file_path = ft_strdup("assets/shotgun.png");
	win->shotgun_texture = get_texture(win->mlx, file_path);
	free(file_path);
	setup_enemies();
	setup_shotgun_sample(&win->gun);
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
	
//	sleep(10);
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
