/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 17:23:55 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/03/21 10:52:20 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"
#include "keys.h"
#include <libft.h>
#include <mlx.h>
#include <stdlib.h>

#include <stdio.h>

static t_image get_display_buffer(void *mlx, uint32_t width, uint32_t height)
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

static void setup_window(t_window *win)
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
     win->mods = (t_mods){10.0};
}

static void print_welcome_msg(char *program_name)
{
     ft_putstr(program_name);
     ft_putendl(": A 42 Graphics Project - by nmayfiel");
     ft_putendl("Controls:");
     ft_putendl("UP/DWN:\tScale");
     ft_putendl("ESC:\tQuit");
}

/*
** 4 is zoom in, 5 is zoom out, for now
*/
int mouse_hook(int button, int x, int y, t_window *win)
{
     t_window *tmp;

     tmp = win;
     printf("%d %d %d\n", button, x, y);
     
     return (0);
}

/*
** Rather than using key hook and mouse hook functions, I chose to use
** the generic mlx_hook function for assigning all event hooks
** You can find the values for event keys in minilibx/mlx_new_window.m
** int mlx_hook(void *win_ptr, int event, int mask, int (*f)(), void *param);
*/

int main(int argc, char **argv)
{
     t_window win;

     if (argc == 1)
     {
	  setup_window(&win);
	  win.initialized = 1;
	  print_welcome_msg(argv[0]);
	  mlx_hook(win.win, 2, 0, remove_key, &win.keys);
	  mlx_hook(win.win, 4, 0, mouse_hook, &win);
	  mlx_hook(win.win, 3, 0, add_key, &win.keys);
	  mlx_hook(win.win, 17, 0, close_hook, &win);
	  mlx_loop_hook(win.mlx, main_loop, &win);
	  mlx_loop(win.mlx);
     }
     else
     {
	  ft_putendl_fd(USAGE, 2);
	  exit(0);
     }
     return (0);
}
