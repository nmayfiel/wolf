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
     x = (-(mods->player_current_tile % level->size_x)) * width + (level->size_x * width) / 2;
     y = (-(mods->player_current_tile / level->size_x)) * height + (level->size_y * height) / 2;
     i = 0;
     while (i < level->size)
     {
	  if (level->map[i] == MAP_WALL)
	       draw_rectangle(img, (t_rect){x, y, width, height, 0x77000000});
	  else if (i == mods->player_current_tile)
	       draw_rectangle(img, (t_rect){x, y, width, height, 0x000000FF});
	  x += width;
	  if ((i + 1) % level->size_x == 0)
	  {
	       x = (-(mods->player_current_tile % level->size_x)) * width + (level->size_x * width) / 2;
	       y += height;
	  }
	  ++i;
     }
}

/*
** radians = degrees * M_PI / 180.0;
** degrees = radians * 180.0 / M_PI;
*/

void update_player(t_mods *mods, double time)
{
	float x;
	float y;
	float vel;
	float vel2;

	vel = mods->player_velocity;
	vel2 = mods->player_strafe_velocity;
	mods->player_angle += mods->player_rotation_factor * (time * 60);
	x = vel * sin((float)mods->player_angle * M_PI / 180.0);
	y = vel * cos((float)mods->player_angle * M_PI / 180.0);
	x += vel2 * sin(clamp_degrees((float)mods->player_angle - 90) * M_PI / 180.0);
	y += vel2 * cos(clamp_degrees((float)mods->player_angle - 90) * M_PI / 180.0);
	mods->player_position_in_tile.x += x * (time * 60);
	mods->player_position_in_tile.y += y * (time * 60);
}

void check_collision(t_level *level, t_mods *mods)
{
     
     if (mods->player_position_in_tile.x > 1023)
     {
	  if (mods->player_current_tile + 1 < level->size)
	  {
	       if ((level->map[mods->player_current_tile + 1] & MAP_WALL) == 0)
	       {
		    mods->player_current_tile += 1;
		    mods->player_position_in_tile.x -= 1023;
	       }
	       else
		    mods->player_position_in_tile.x = 1010;
	  }
	  else
	  {
	       mods->player_position_in_tile.x = 1010;
	  }
     }
     else if (mods->player_position_in_tile.x < 0)
     {
	  if (mods->player_current_tile - 1 > 0)
	  {
	       if ((level->map[mods->player_current_tile - 1] & MAP_WALL) == 0)
	       {
		    mods->player_current_tile -= 1;
		    mods->player_position_in_tile.x += 1023;
	       }
	       else
		    mods->player_position_in_tile.x = 9;
	  }
	  else
	  {
	       mods->player_position_in_tile.x = 9;
	  }    
     }
     if (mods->player_position_in_tile.y > 1023)
     {
	  if (mods->player_current_tile - level->size_x > 0)
	       if ((level->map[mods->player_current_tile - level->size_x] & MAP_WALL) == 0)
	       {
		    mods->player_current_tile -= level->size_x;
		    mods->player_position_in_tile.y -= 1023;
	       }
	       else
		    mods->player_position_in_tile.y = 1010;
	  else
	       mods->player_position_in_tile.y = 1010;
	  
     }
     else if (mods->player_position_in_tile.y < 0)
     {
	  if (mods->player_current_tile + level->size_x < level->size)
	       if ((level->map[mods->player_current_tile + level->size_x] & MAP_WALL) == 0)
	       {
		    mods->player_current_tile += level->size_x;
		    mods->player_position_in_tile.y += 1023;
	       }
	       else
		    mods->player_position_in_tile.y = 10;
	  else
	       mods->player_position_in_tile.y = 10;
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
     clear_image(&win->disp, 0x00FFFFFF);

     manipulate_vertical_image(&win->vertical_buffer, win->disp.size_in_pixels);
     mlx_put_image_to_window(win->mlx, win->win, win->disp.ptr,
			     win->center.x - win->disp.center.x,
			     win->center.y - win->disp.center.y);
     
     mlx_put_image_to_window(win->mlx, win->win, win->title_texture.ptr,
			     win->center.x - win->title_texture.center.x,
			     (win->center.y * 0.75) - win->title_texture.center.y);
     mlx_string_put(win->mlx,
		    win->win,
		    win->center.x - 35,
		    win->center.y * 1.1,
		    0x00990000,
		    "[ENTER]");     
}

float		clamp_degrees_f(float angle)
{
	float new_angle;

	new_angle = angle;
	if (new_angle >= 180)
		new_angle = -180.0 + (new_angle - 180.0);
	if (new_angle < -180.0)
		new_angle = 180.0 + (new_angle + 180.0);
	return (new_angle);
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

	sample_texture = (int32_t *)win->wall_texture.data;
	buff = win->vertical_buffer;
	row = mods->player_current_tile / level->size_x;
	col = mods->player_current_tile % level->size_x;
	max_x = level->size_x * 1024;
	max_y = level->size_y * 1024;
	x = ((col) * 1024) + mods->player_position_in_tile.x;
	y = ((row) * 1024) + 1023 - mods->player_position_in_tile.y;

	angle = (float)clamp_degrees(mods->player_angle -  30);
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
			i = 0;

			wall_height = ABS((float)1024 / (float)distance) * 864.0;
			margin = (768 - wall_height) / 2;
			while (i < 768)
			{
				if (i < margin)
					*(buff[(768 * step) + i]) = 0x0033333c;
				else if (i < wall_height + margin)
				{
					int32_t place_in_texture = ((float)(i - margin) / wall_height) * 1024;
					*(buff[(768 * step) + i]) = sample_texture[(1024 * place_in_texture_x) + place_in_texture];
					//sample_texture
				}
				else
					*(buff[(768 * step) + i]) = 0x00999999;
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

/*
** Rendering enemies:
** 	* find the difference between your rotations to determine which angle
	the enemy should be

	* the images will need to be displayed forward and backward

	* You can easily determine the size of the enemy based on the distance

	* You need a function to put an image to another image in order to scale it.

	* You will need to calculate where on the floor the enemy should show up
	* in addition, you need to calculate where the horizon line is in order
	* to display where your walls are, and how much padding to put on the top
	* and bottom of it, rather than just splitting it in half.

*/

// cacodemon has 34 images
// forward or backward (1 or -1)
// top left corner: 308, 11
// sample size: 67, 67

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
	static int32_t enemy_index = 0;
	static double time = 0;
	static int32_t shotgun_index = 0;
	int32_t perturb_y;

	if (win->mods.player_velocity != 0 || win->mods.player_strafe_velocity != 0)
		perturb_y = cos(5 * M_PI * win->time) * 4;
	else
		perturb_y = 0;
	if (win->mods.should_fire && win->gun.shooting_anim == 0)
	{
		win->gun.shooting_anim = 1;
		win->gun.default_anim = 0;
		win->gun.shooting_anim_time = win->time;
	}
	if (win->time - time > 0.07)
	{
		++enemy_index;
		time = win->time;
		if (enemy_index > 7)
			enemy_index = 0;
	}
	if (win->gun.default_anim)
	{
		if (win->time - win->gun.default_start_time > win->gun.default_time_per_frame)
		{
			++shotgun_index;
			if (shotgun_index > win->gun.default_anim_end_frame)
				shotgun_index = win->gun.default_anim_start_frame;
			win->gun.default_start_time = win->time;
		}
	}
	else if (win->gun.shooting_anim)
	{
		if (win->time - win->gun.shooting_anim_time > win->gun.shooting_anim_time_per_frame)
		{
			++shotgun_index;
			if (shotgun_index > win->gun.shooting_anim_frame_end)
			{
				shotgun_index = win->gun.default_anim_start_frame;
				win->gun.default_anim = 1;
				win->gun.shooting_anim = 0;
			}
			win->gun.shooting_anim_time = win->time;
		}
	}
	mlx_clear_window(win->mlx, win->win);
	if (win->game_state & GS_NORME)
	{
		clear_image(&win->disp, 0x00000000);
		update_player(&win->mods, win->frame_time);
		check_collision(&win->level, &win->mods);
		raycasting(win, &win->level, &win->mods);
//		draw_enemy_at_point(enemy_index, &win->disp, &win->enemy_texture, win->disp.center.x - 150, win->disp.center.y - 150);
		draw_gun(shotgun_index, win->gun, &win->disp, &win->shotgun_texture, win->disp.center.x - 146, win->disp.height - 396 + perturb_y);
		put_minimap_to_image(&win->disp, &win->level, &win->mods);
	}
	mlx_put_image_to_window(win->mlx, win->win, win->disp.ptr,
					win->center.x - win->disp.center.x,
					win->center.y - win->disp.center.y);
	//mlx_put_image_to_window(win->mlx, win->win, win->shotgun_texture.ptr,
	//			win->center.x - win->shotgun_texture.center.x,
	//			win->center.y - win->shotgun_texture.center.y);
	if (win->game_state & GS_PAUSE)
		mlx_string_put(win->mlx,
			       win->win,
			       win->center.x - 40,
			       win->center.y,
			       0x00990000,
			       "[Paused]");
}
