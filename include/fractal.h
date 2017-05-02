/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 18:00:47 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/03/21 11:05:01 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H

# include <libft.h>
# include "keys.h"

# define WIN_NAME	"Fractal"
# define USAGE "Usage: ./fractol <type>"

/*
** WINDOW
*/

# define WIN_WIDTH		768
# define WIN_HEIGHT		512
# define CLEAR_COLOR 0x00000000

/*
** ERRORS
*/

# define E_MALLOC 3
# define EMSG_MALLOC "Allocation error"


typedef struct s_f2
{
     float x;
     float y;
} t_f2;

typedef struct		s_point
{
	int32_t	x;
	int32_t	y;
}					t_point;


/*
** Values modified by keys
*/
typedef struct s_mods
{
     float scale;
     float xmouse;
     float ymouse;
     int32_t update;
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
}					t_window;

t_image				get_splash(void *mlx);
void				render_splash(t_window *win);

void clear_image(t_window *win, int32_t color);
void				render(t_window *win);

int32_t					main_loop(t_window *win);
int32_t close_hook(t_window *win);

#endif
