/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 18:00:47 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/06/30 00:05:54 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <libft.h>

# define WIN_NAME	"WOLFENSTEIN"

# define WIN_WIDTH	1024
# define WIN_HEIGHT	768
# define DATA_SIZE	(1024 * 768)
# define CLEAR_COLOR	0x00000000

# define E_MALLOC	3
# define EMSG_MALLOC	"Allocation error"

# define MAP_NONE	0
# define MAP_WALL	1
# define MAP_HERO	1 << 1
# define MAP_ENEMY 1 << 2

# define GS_SPLASH	1
# define GS_TITLE	1 << 1
# define GS_PAUSE	1 << 2
# define GS_NORME	1 << 3

typedef struct		s_f2
{
	float x;
	float y;
}				t_f2;

typedef struct		s_double2
{
	double x;
	double y;
}				t_double2;

typedef struct		s_point
{
	int32_t	x;
	int32_t	y;
}					t_point;

typedef struct		s_key
{
	uint32_t ended_down;
	uint32_t changed;
}			t_key;

typedef struct		s_keys
{
	t_key	close;
	t_key	up;
	t_key	down;
	t_key	up_arrow;
	t_key	down_arrow;
	t_key	left;
	t_key	right;
	t_key	left_alt;
	t_key	right_alt;
	t_key	enter;
	t_key	pause;
//	t_key   fire;
}			t_keys;

typedef struct		s_mouse
{
	int32_t		click1;
	int32_t		click2;
	t_double2	location;
}				t_mouse;

typedef struct		s_tx_sample
{
	int32_t x;
	int32_t y;
	int32_t x_dir;
	int32_t y_dir;
	int32_t width;
	int32_t height;
}				t_tx_sample;

typedef struct		s_gun
{
	t_tx_sample	sample_data[11];

	int32_t		default_anim;
	int32_t		default_anim_start_frame;
	int32_t		default_anim_end_frame;
	double		default_time_per_frame;
	double		default_start_time;

	int32_t		shooting_anim;
	double		shooting_anim_time;
	double		shooting_anim_time_per_frame;
	double		shooting_anim_frame_start;
	double		shooting_anim_frame_end;
}				t_gun;

//typedef struct	s_hsv_colors
//{
//	int32_t colors[360];
//	double s;
//	double v;
//}				t_hsv_colors;

typedef struct		s_enemy
{
	uint32_t	current_tile;
	t_f2		position_in_tile;
	float		velocity;
	int32_t		rotation_factor;
	int32_t		angle;
	int32_t		should_fire;
	
}				t_enemy;

typedef struct		s_mods
{
	uint32_t	player_current_tile;
	t_f2		player_position_in_tile;
	float		player_velocity;
	float		player_strafe_velocity;
	float		look_offset;
	int32_t		look_angle;
	float		vertical_velocity;
	float		height_multiplier;
	int32_t		player_rotation_factor;
	int32_t		player_angle;
	//t_double2	click;
	//t_double2	mouse;
	int32_t		update;
	int32_t		should_fire;
	t_enemy		enemy;
}				t_mods;

typedef struct		s_image
{
	void	*ptr;
	int8_t	*data;
	int32_t	bpp;
	int32_t	size_line;
	int32_t	size_in_bytes;
	int32_t	size_in_pixels;
	int32_t	endian;
	int32_t	height;
	int32_t	width;
	t_point	center;
}					t_image;

typedef struct		s_level
{
	uint8_t		*map;
	uint32_t	size;
	uint32_t	size_x;
	uint32_t	size_y;
}				t_level;

typedef struct		s_rect
{ 
	int32_t	x;
	int32_t	y;
	int32_t	width;
	int32_t	height;
	int32_t	color;
}				t_rect;

typedef struct		s_clock
{
	double		time;
	double		last_frame_time;
	uint64_t	last_update;
}				t_clock;

typedef struct		s_window
{
	void		*mlx;
	void		*win;
	t_clock		clock;
	t_image		disp;
	int32_t		**vertical_buffer;
	t_image		splash;
	t_image		splash_mask;
	t_image		title_texture;
	t_image		enemy_texture;
	t_image		wall_texture;
	t_image		shotgun_texture;
	t_image		minimap;
	t_gun 		gun;
	t_point		center;
	t_keys		keys;
	t_mouse		mouse;
	t_mods		mods;
	int			initialized;
	int32_t		opts;
	t_level		level;
	uint32_t	game_state;
}					t_window;

void				render_title(t_window *win);
void				render_game(t_window *win);
void				render_splash(t_window *win);

int32_t				key_down(int32_t kc, t_keys *keys);
int32_t				key_up(int32_t kc, t_keys *keys);

void				clear_image(t_image *img, int32_t color);
void				draw_rectangle(t_image *img, t_rect rect);
//void				calculate_rgb_from_hsv(int32_t colors[360], const float s, const float v);

t_image				get_splash(void *mlx);
t_image				get_splash_mask(void *mlx, int32_t width, int32_t height);

int32_t				read_level_map(const char *fn, t_level *level, t_mods *mods);
int				parse_options(int num_opts, char **opts, t_window *win);

int32_t				main_loop(t_window *win);
int32_t				mouse_hook(int button, int x, int y, t_window *win);
int32_t				mouse_moved(int x, int y, t_window *win);
int32_t				close_hook(t_window *win);

void				print_usage(char *name);
void				exit_error(int32_t error_code);

int32_t				clamp_degrees(int32_t angle);
float				clamp_degrees_f(float angle);

#endif
