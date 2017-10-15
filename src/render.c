#include <libft.h>
#include "wolf.h"
#include <mlx.h>
#include <math.h>

#include <stdio.h>
#include <stdlib.h>

void put_minimap_to_image(t_image *img, t_level *level, t_mods *mods)
{
     int32_t width;
     int32_t height;
     int32_t x;
     int32_t y;
     uint32_t i;

     height = 10;
     width = 10;
     x = ((-(mods->player_current_tile % level->size_x)) * width) + img->width / 2;
     y = ((-(mods->player_current_tile / level->size_x)) * height) + img->height / 2;
     i = 0;
     while (i < level->size)
     {
	  if (level->map[i] == MAP_WALL)
	       draw_rectangle(img, (t_rect){x, y, width, height, 0x99FFFFFF});
	  else if (i == mods->player_current_tile)
	       draw_rectangle(img, (t_rect){x, y, width, height, 0xAAFF0000});
	  x += width;
	  if ((i + 1) % level->size_x == 0)
	  {
	       x = (-(mods->player_current_tile % level->size_x)) * width + img->width /2;
	       y += height;
	  }
	  ++i;
     }
}



void manipulate_vertical_image(int32_t ***buffer, uint32_t size)
{
     int32_t **buff;
     uint32_t i;
     uint8_t r;
     
     i = 0;
     r = 0;
     buff = *buffer;
     while (i < size)
     {
	     if ((i / 256) % 3 == 0)
	     	     *(buff[i]) = 0x00FFFFFF;
	     else
	     	     *(buff[i]) = 0x00DEDEDE;		     
	     ++r;
	     ++i;
     }
}

void	render_title(t_window *win)
{
     mlx_clear_window(win->mlx, win->win);
     clear_image(&win->assets.display_buffer, 0x00FFFFFF);

     manipulate_vertical_image(&win->assets.vertical_buffer, win->assets.display_buffer.size_in_pixels);
     mlx_put_image_to_window(win->mlx, win->win, win->assets.display_buffer.ptr,
			     win->center.x - win->assets.display_buffer.center.x,
			     win->center.y - win->assets.display_buffer.center.y);
     
     mlx_put_image_to_window(win->mlx, win->win, win->assets.title_texture.ptr,
			     win->center.x - win->assets.title_texture.center.x,
			     (win->center.y * 0.75) - win->assets.title_texture.center.y);
     mlx_string_put(win->mlx,
		    win->win,
		    win->center.x - 35,
		    win->center.y * 1.1,
		    0x00990000,
		    "[ENTER]");     
}



int32_t mul_color(int32_t color, double multiplier)
{
	uint8_t r;
	uint8_t g;
	uint8_t b;

	r = (color & 0x000000FF) * multiplier;
	g = ((color & 0x0000FF00) >> 8) * multiplier;
	b = ((color & 0x00FF0000) >> 16) * multiplier;
	return (r | (g << 8) | (b << 16));
}

void	raycasting(t_window *win, t_level *level, t_mods *mods)
{
	int32_t **buff;
	int32_t row;
	int32_t col;
	int32_t x;
	int32_t y;
	int32_t max_x;
	int32_t max_y;
	int32_t dy;
	int32_t dx;

	int32_t opposite;
	int32_t adjascent;
	int32_t hypotenuse;
	float distance;
	t_point ray;
	int32_t tile_to_check;
	int32_t color;
	int32_t newcolor;

	float angle;
	float beta;
	float angle_step;
	int32_t step;

	int32_t i;
	uint32_t di;
	int32_t wall_height;
	int32_t margin;
	int32_t *sample_texture;
	int32_t place_in_texture_x;
	int32_t new_place_in_texture_x;

	sample_texture = (int32_t *)win->assets.wall_texture.data;
	buff = win->assets.vertical_buffer;
	row = mods->player_current_tile / level->size_x;
	col = mods->player_current_tile % level->size_x;
	max_x = level->size_x * 1024;
	max_y = level->size_y * 1024;
	x = ((col) * 1024) + mods->player_position_in_tile.x;
	y = ((row) * 1024) + 1023 - mods->player_position_in_tile.y;

	angle = clamp_degrees_f(mods->player_angle - 30.0);
	angle_step = 60.0 / 1024.0;
	step = 0;
	while (step < 1024)
	{
		distance = 0;

		ray.y = ((y / 1024) * 1024);
		ray.y += angle > -90 && angle <= 90 ? -1 : 1024;
		color = angle > -90 && angle <= 90 ? 0x00FF00FF : 0x0000FFFF;
		dy = angle > -90 && angle <= 90 ? -1024 : 1024;
		dx = 1024 / tan(angle * M_PI / 180.0);
		adjascent = y - ray.y;
		opposite = adjascent * tan(angle * M_PI / 180.0);
		hypotenuse = ABS(adjascent) / cos(angle * M_PI / 180.0);
		ray.x = x + opposite;
		di = 0;
		while (di < level->size_y && distance == 0)
		{
			adjascent = y - ray.y;
			opposite = adjascent * tan(angle * M_PI / 180.0);
			hypotenuse = ABS(adjascent) / cos(angle * M_PI / 180.0);
			ray.x = x + opposite;
			if (ray.x > 0 && ray.x < max_x)
			{
				tile_to_check = ((ray.y / 1024) * level->size_x) + (ray.x / 1024);
				if (level->map[tile_to_check] == 1)
				{
					beta = angle - (float)mods->player_angle;
					distance = hypotenuse * cos(beta * M_PI / 180.0);
					place_in_texture_x = ray.x % 1024;
				}
			}
			ray.y += dy;
			++di;
		}
		
		ray.x = ((x / 1024) * 1024);
		angle = clamp_degrees_f(angle);
		ray.x += angle > 0 ? 1024 : -1;
		newcolor = angle > 0 ? 0x00FFFF00 : 0x0000FF00;
		dx = angle > 0 ? 1024 : -1024;
		dy = 1024 * tan(clamp_degrees_f(angle - 90) * M_PI / 180.0);
		adjascent = ray.x - x;

		opposite = adjascent * tan(clamp_degrees_f(angle - 90) * M_PI / 180.0);
		hypotenuse = ABS(adjascent) / cos(clamp_degrees_f(angle - 90) * M_PI / 180.0);
		
		ray.y = y + opposite;
		di = 0;
		float newdistance;
		newdistance = 0;
		while (di < level->size_x && newdistance == 0)
		{
			adjascent = ray.x - x;

			opposite = adjascent * tan(clamp_degrees_f(angle - 90) * M_PI / 180.0);
			hypotenuse = ABS(adjascent) / cos(clamp_degrees_f(angle - 90) * M_PI / 180.0);
		
			ray.y = y + opposite;
			if (ray.y > 0 && ray.y < max_y)
			{
				tile_to_check = ((ray.y / 1024) * level->size_x) + (ray.x / 1024);
				if (level->map[tile_to_check] == 1)
				{
					beta = angle - (float)mods->player_angle;
					newdistance = hypotenuse * cos(beta * M_PI / 180.0);
					new_place_in_texture_x = ray.y % 1024;
				}
			}
			ray.x += dx;
			++di;
		}

		if ((ABS(distance) > ABS(newdistance) && newdistance != 0) || distance == 0)
		{
			distance = newdistance;
			color = newcolor;
			place_in_texture_x = new_place_in_texture_x;
		}
		
		if (distance != 0)
		{
//			printf("%f\n", (1024 / 2) / tan(30 / M_PI * 2.0));
			i = 0;
			double distance_multiplier = 1.0 - ABS(distance / 20480.0);
			if (distance_multiplier < 0)
				distance_multiplier = 0;
			wall_height = ABS((float)1024 / (float)distance) * 864.0;
			// Jump multiplier should be a value between 0.5 and 1.5;
			margin = (((768 - wall_height) / 2) * mods->height_multiplier) + mods->look_angle;
			while (i < 768)
			{
				if (i < margin)
					*(buff[(768 * step) + i]) = 0x00000000;//0x0033333c;
				else if (i < wall_height + margin)
				{
					int32_t place_in_texture = ((float)(i - margin) / wall_height) * 1024;
					*(buff[(768 * step) + i]) = mul_color(sample_texture[(1024 * place_in_texture_x) + place_in_texture], distance_multiplier);
					//sample_texture
				}
				else
					*(buff[(768 * step) + i]) = 0x00000000;//0x00999999;
				++i;
			}
		}
		else
		{
			i = 0;
			margin = 768 / 2;
			while (i < 768)
			{
				if (i < margin)
					*(buff[(768 * step) + i]) = 0x00333339;
				else
					*(buff[(768 * step) + i]) = 0x00999999;
				++i;
			}
		}
		
		angle += angle_step;
		step++;
	}
}

extern t_tx_sample enemies[34];

void	draw_enemy_at_point(int32_t enemy_index, t_image *img, t_image *src, int32_t x, int32_t y)
{
	int32_t width = 300;
	int32_t height = 300;
	int32_t ssize;
	int32_t *data;
	int32_t *src_data;
	int32_t i;
	int32_t si;
	int32_t sx;
	int32_t sy;
	int32_t x2;
	int32_t y2;

	data = (int32_t *)img->data;
	src_data = (int32_t *)src->data;
	y2 = 0;
	ssize = 67;
	while (y2 < height)
	{
		x2 = 0;
		while (x2 < width)
		{
			if (x + x2 < img->width && x + x2 >= 0 && y + y2 >= 0 && y + y2 < img->height)
			{
				i = x + x2 + (img->width * (y + y2));
				if (enemies[enemy_index].x_dir == 1)
					sx = enemies[enemy_index].x + (((float)x2 / (float)width) * ssize);
				else if (enemies[enemy_index].x_dir == -1)
					sx = enemies[enemy_index].x + (ssize - (((float)x2 / (float)width) * ssize));
				sy = enemies[enemy_index].y + (((float)y2 / (float)height) * ssize);
				si = sx + (sy * src->width);
				if (!(src_data[si] & 0xFF000000) && i < img->size_in_pixels && i >= 0 && si < src->size_in_pixels && si >= 0)
					data[i] = src_data[si];
			}
			++x2;
		}
		++y2;
	}
}

//extern t_tx_sample shotguns[11];

void draw_gun(int32_t shotgun_index, t_gun gun, t_image *img, t_image *src, int32_t x, int32_t y)
{
	int32_t width = 292;
	int32_t height = 400;
	int32_t *data;
	int32_t *src_data;
	int32_t i;
	int32_t si;
	int32_t sx;
	int32_t sy;
	int32_t x2;
	int32_t y2;

	data = (int32_t *)img->data;
	src_data = (int32_t *)src->data;
	y2 = 0;
	while (y2 < height)
	{
		x2 = 0;
		while (x2 < width)
		{
			if (x + x2 < img->width && x + x2 >= 0 && y + y2 >= 0 && y + y2 < img->height)
			{
				i = (x + x2) + (img->width * (y + y2));
				sx = gun.sample_data[shotgun_index].x + (((float)x2 / (float)width)
								  * gun.sample_data[shotgun_index].width);
				sy = gun.sample_data[shotgun_index].y + (((float)y2 / (float)height)
								  * gun.sample_data[shotgun_index].height);
				si = sx + (sy * src->width);
				if (!(src_data[si] & 0xFF000000) && i < img->size_in_pixels && i >= 0 && si < src->size_in_pixels && si >= 0)
					data[i] = src_data[si];
			}
			++x2;
		}
		++y2;
	}
}

void	render_game(t_window *win)
{
	mlx_clear_window(win->mlx, win->win);
	if (win->game_state & GS_NORME)
	{
		clear_image(&win->assets.display_buffer, 0x00000000);
		clear_image(&win->assets.minimap, 0xFF000000);
		raycasting(win, &win->level, &win->mods);
		draw_gun(win->assets.gun.current_sprite, win->assets.gun, &win->assets.display_buffer, &win->assets.shotgun_texture, win->assets.display_buffer.center.x - 146, win->assets.display_buffer.height - 396 + win->assets.gun.perturb_y);
		put_minimap_to_image(&win->assets.minimap, &win->level, &win->mods);
	}
	mlx_put_image_to_window(win->mlx, win->win, win->assets.display_buffer.ptr,
					win->center.x - win->assets.display_buffer.center.x,
					win->center.y - win->assets.display_buffer.center.y);
	mlx_put_image_to_window(win->mlx, win->win, win->assets.minimap.ptr,
				10,
				10);
	if (win->game_state & GS_PAUSE)
		mlx_string_put(win->mlx,
			       win->win,
			       win->center.x - 40,
			       win->center.y,
			       0x00990000,
			       "[Paused]");
}
