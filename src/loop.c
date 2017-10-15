/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 21:01:02 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/08/10 02:46:55 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "math.h"
#include <mlx.h>

void update_player(t_mods *mods, t_mouse mouse, double dt)
{
	float x;
	float y;
	float vel;
	float vel2;

	mods->player_angle = clamp_degrees_f(mods->player_angle);
	vel = mods->player_velocity;
	vel2 = mods->player_strafe_velocity;
	mods->player_angle += (mouse.diff.x * 0.25) * (dt * 60);
	x = vel * sin((float)mods->player_angle * M_PI / 180.0);
	y = vel * cos((float)mods->player_angle * M_PI / 180.0);
	x += vel2 * sin(clamp_degrees_f((float)mods->player_angle - 90) * M_PI / 180.0);
	y += vel2 * cos(clamp_degrees_f((float)mods->player_angle - 90) * M_PI / 180.0);
	mods->player_position_in_tile.x += x * (dt * 60);
	mods->player_position_in_tile.y += y * (dt * 60);
	mods->look_angle -= (mouse.diff.y) * (dt * 60);
}

void check(t_level *level, float *pos, uint32_t *tile, int32_t step)
{
	if (*pos > 1023)
	{
		if (*tile + step < level->size
		    && (level->map[*tile + step] & MAP_WALL) == 0)
		{
			*tile += step;
			*pos -= 1023;
		}
		else
			*pos = 1010;
	}
	else if (*pos < 0)
	{
		if (*tile - step > 0
		    && (level->map[*tile - step] & MAP_WALL) == 0)
		{
			*tile -= step;
			*pos += 1023;
		}
		else
			*pos = 10;
	}
}

void check_collision(t_level *level, t_mods *mods)
{
	check(level, &mods->player_position_in_tile.x,
	      &mods->player_current_tile, 1);
	check(level, &mods->player_position_in_tile.y,
	      &mods->player_current_tile, -level->size_x);
}

int32_t			gun_animation(t_mods *mods, t_gun *gun, double time, double dt)
{
	if (mods->player_velocity != 0 || mods->player_strafe_velocity != 0)
		gun->perturb_y = (cos(5 * M_PI * time) * 4) * (dt * 60);
	if (mods->should_fire && gun->shooting_anim == 0)
	{
		gun->shooting_anim = 1;
		gun->shooting_anim_time = time;
	}
	if (gun->shooting_anim)
	{
		if (time - gun->shooting_anim_time > gun->shooting_anim_time_per_frame)
		{
			++gun->current_sprite;
			if (gun->current_sprite > gun->shooting_anim_frame_end)
			{
				gun->current_sprite = gun->default_sprite;
				gun->shooting_anim = 0;
			}
			gun->shooting_anim_time = time;
		}
		return (1);
	}
	else
		gun->current_sprite = gun->default_sprite;
	return (0);
}

int32_t			update_animations(t_mods *mods, t_assets *assets,
					  double time, double dt)
{
	int32_t needs_render;

	needs_render = 0;
	needs_render |= gun_animation(mods, &assets->gun, time, dt);
	return (needs_render);
}

int32_t			main_loop(t_window *win)
{
	update_clock(&win->clock);
	handle_input(&win->keys, &win->mouse, &win->mods, win);
	if (win->is_initialized == 1)
	{
		if (win->game_state & GS_SPLASH)
			render_splash(win);
		else if (win->game_state & GS_TITLE)
			render_title(win);
		else if (win->game_state & GS_NORME)
		{
			update_animations(&win->mods, &win->assets, win->clock.time,
					  win->clock.last_frame_time);
			update_player(&win->mods, win->mouse,
				      win->clock.last_frame_time);
			check_collision(&win->level, &win->mods);
			render_game(win);
		}
		else if (win->game_state & GS_PAUSE && win->keys.pause.changed)
			render_game(win);
	}
	reset_input(&win->keys, &win->mouse);
	return (0);
}
