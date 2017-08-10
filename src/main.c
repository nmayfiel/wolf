/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 17:23:55 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/08/10 02:59:57 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int					expose_hook(int code, t_window *win)
{
	if (code == 0 || code == 1)
	{
		win->game_state = GS_PAUSE;
		win->keys.pause.changed = 1;
		nx_mouse_set_cursor_association(win->win, 1);
		nx_display_cursor(win->win, 1);
	}
	return (0);
}

int32_t			close_hook(t_window *win)
{
	mlx_destroy_window(win->mlx, win->win);
	exit(0);
}

int32_t resize_hook(t_window *win)
{
	render_game(win);
	return (0);
}

t_tx_sample			enemies[34];

void				setup_enemies(void)
{
	int i;

	enemies[0] = (t_tx_sample){308, 11, 1, 1, 67, 67};
	enemies[1] = (t_tx_sample){236, 12, 1, 1, 67, 67};
	enemies[2] = (t_tx_sample){159, 9, 1, 1, 67, 67};
	enemies[3] = (t_tx_sample){91, 11, 1, 1, 67, 67};
	enemies[4] = (t_tx_sample){18, 12, 1, 1, 67, 67};
	enemies[5] = (t_tx_sample){91, 11, -1, 1, 67, 67};
	enemies[6] = (t_tx_sample){159, 9, -1, 1, 67, 67};
	enemies[7] = (t_tx_sample){236, 12, -1, 1, 67, 67};
	i = 8;
	while (i < 34)
	{
		enemies[i] = (t_tx_sample){0, 0, 1, 1, 67, 67};
		++i;
	}
}

void				setup_shotgun_sample(t_gun *gun)
{
	int i;

	gun->sample_data[0] = (t_tx_sample){26, 0, 1, 1, 70, 96};
	gun->sample_data[1] = (t_tx_sample){106, 0, 1, 1, 70, 96};
	gun->sample_data[2] = (t_tx_sample){182, 0, 1, 1, 70, 96};
	gun->sample_data[3] = (t_tx_sample){256, 0, 1, 1, 70, 96};
	i = 4;
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

static void			init_assets(void *mlx, t_assets *assets)
{
	char *file_path;

	assets->display_buffer = get_image_of_size(mlx, WIN_WIDTH, WIN_HEIGHT);
	file_path = ft_strdup("assets/splash.png");
	assets->splash = get_texture(mlx, file_path);
	free(file_path);
	assets->splash_mask = get_image_of_size(mlx, WIN_WIDTH, WIN_HEIGHT);
	clear_image(&assets->splash_mask, 0x00FFFFFF);
	assets->vertical_buffer =
		get_vertical_image_buffer_map(&assets->display_buffer);
	assets->minimap = get_image_of_size(mlx, 200, 150);
	file_path = ft_strdup("assets/title_texture.png");
	assets->title_texture = get_texture(mlx, file_path);
	free(file_path);
	file_path = ft_strdup("assets/brick_wall.png");
	assets->wall_texture = get_texture(mlx, file_path);
	free(file_path);
	file_path = ft_strdup("assets/cacodemon.png");
	assets->enemy_texture = get_texture(mlx, file_path);
	free(file_path);
	file_path = ft_strdup("assets/shotgun.png");
	assets->shotgun_texture = get_texture(mlx, file_path);
	free(file_path);
	setup_enemies();
	setup_shotgun_sample(&assets->gun);
}

static void			init_window(t_window *win)
{
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	win->clock = (t_clock){0.0, 0.0, 0};
	win->center.x = (WIN_WIDTH / 2);
	win->center.y = (WIN_HEIGHT / 2);
	win->keys = (t_keys){
		{0, 0}, {0, 0},
		{0, 0}, {0, 0},
		{0, 0}, {0, 0},
		{0, 0}, {0, 0},
		{0, 0}
	};
	win->is_initialized = 0;
	win->mods = (t_mods){0, {612, 612}, 0, 0, 0, 0, 0, 1.0,
		0, 0, 0, 0, 0, {0, {612, 612}, 0, 0, 0, 0}};
	win->game_state = GS_SPLASH;
	init_assets(win->mlx, &win->assets);
}

int					main(void)
{
	t_window	win;

	init_window(&win);
	if (read_level_map("assets/map.wolf", &win.level, &win.mods) != 1)
		exit(0);
	win.is_initialized = 1;
	ft_putendl("WOLF 3D: A 42 Graphics Project - by nmayfiel");
	nx_mouse_set_cursor_association(win.win, 0);
	nx_display_cursor(win.win, 0);
	mlx_key_down(win.win, key_down, &win.keys);
	mlx_key_up(win.win, key_up, &win.keys);
	mlx_mouse_click_hook(win.win, mouse_hook, &win);
	mlx_mouse_moved_hook(win.win, mouse_moved, &win);
	mlx_expose_hook(win.win, expose_hook, &win);
	mlx_close_hook(win.win, close_hook, &win);
	mlx_loop_hook(win.mlx, main_loop, &win);
	mlx_resize_hook(win.win, resize_hook, &win);
	mlx_loop(win.mlx);
	return (0);
}
