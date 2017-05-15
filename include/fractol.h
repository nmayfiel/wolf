/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 18:00:47 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/05/14 20:53:09 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H

# include <libft.h>
# include <keys.h>
# include <OpenCL/opencl.h>


# define WIN_NAME	"Fractal"

/*
** WINDOW
*/

# define WIN_WIDTH		1000
# define WIN_HEIGHT		768
# define DATA_SIZE (1000 * 768)
# define CLEAR_COLOR 0x00000000

/*
** ERRORS
*/

# define E_MALLOC 3
# define EMSG_MALLOC "Allocation error"

/*
** OPTIONS BITMASK
*/

# define OPT_JULIA 1
# define OPT_MANDELBROT 1 << 1
# define OPT_SHIP 1 << 2
# define OPT_GPU 1 << 3
# define OPT_64 1 << 4

typedef struct s_f2
{
     double x;
     double y;
} t_f2;

typedef struct		s_point
{
	int32_t	x;
	int32_t	y;
}					t_point;

/*
** OpenCL Struct
*/

typedef struct s_cl_device
{
     cl_device_id device_id;
     cl_context context;
     cl_command_queue commands;
     cl_program program;
     cl_kernel kernel;
     cl_mem output;
     size_t local;
} t_cl_device;

/*
** Values modified by keys
*/
typedef struct s_mods
{
     double scale;
     double xmouse;
     double ymouse;
     int32_t update;
     int32_t color_index;
     int32_t iterations;
     double xoffset;
     double yoffset;
} t_mods;

typedef struct		s_image
{
	void	*ptr;
	int8_t	*data;
	int32_t	bpp;
	int32_t	size_line;
     int32_t size_in_bytes;
	int32_t	endian;
	int32_t	height;
	int32_t	width;
	t_point	center;
}					t_image;

typedef struct		s_window
{
	void		*mlx;
	void		*win;
	double		time;
	t_image		disp;
	t_image		splash;
	t_point		center;
	t_keys		keys;
     t_mods mods;
	int			initialized;
     int32_t opts;
     t_cl_device cl;
}					t_window;

/*
** Splash Screen
*/

t_image				get_splash(void *mlx);
void				render_splash(t_window *win);

/*
** MLX Helpers
*/

void clear_image(t_window *win, int32_t color);
void				render(t_window *win);

/*
** OpenCL Helpers
*/

void create_cl_device(t_cl_device *cl, int32_t *win_opts);
void release_cl_device(t_cl_device *cl);

/*
** Fract'ol
*/

void print_usage(char *name);
void exit_error(int32_t error_code);
int parse_options(int num_opts, char **opts, t_window *win);
int32_t					main_loop(t_window *win);
int32_t mouse_hook(int button, int x, int y, t_window *win);
int32_t mouse_moved(int x, int y, t_window *win);
int32_t close_hook(t_window *win);


#endif
