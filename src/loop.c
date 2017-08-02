/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 21:01:02 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/08/02 02:52:17 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "wolf.h"
#include <stdlib.h>
#include <mlx.h>
#include <mach/mach_time.h>

#include <stdio.h>

int32_t			close_hook(t_window *win)
{
	mlx_destroy_window(win->mlx, win->win);
	exit(0);
}

int32_t		clamp_degrees(int32_t angle)
{
	int32_t new_angle;

	new_angle = angle;
	if (new_angle == -180)
		new_angle = 180;
	if (new_angle > 180)
		new_angle = -180 + new_angle - 180;
	return (new_angle);
}

// if up ended down and down did not -> do velocity
double			seconds_per_frame(uint64_t last,
					  uint64_t current)
{
     static mach_timebase_info_data_t tb;
     uint64_t elapsed;
     uint64_t nanosecs;

     elapsed = current - last;
     if (tb.denom == 0)
	  mach_timebase_info(&tb);
     nanosecs = elapsed * tb.numer / tb.denom;
     return ((double)nanosecs * 1.0E-9);
}


void	reset_input(t_keys *keys, t_mouse *mouse)
{
	keys->close.changed = 0;
	keys->up.changed = 0;
	keys->down.changed = 0;
	keys->left.changed = 0;
	keys->right.changed = 0;
	keys->enter.changed = 0;
	keys->pause.changed = 0;
	keys->right_alt.changed = 0;
	keys->left_alt.changed = 0;
	//keys->fire.changed = 0;
	keys->up_arrow.changed = 0;
	keys->down_arrow.changed = 0;
	mouse->click1 = 0;
	mouse->click2 = 0;
	mouse->diff.x = 0.0;
	mouse->diff.y = 0.0;
}

void			update_clock(t_clock *clock)
{
	uint64_t current_time;

	current_time = mach_absolute_time();
	clock->last_frame_time = seconds_per_frame(clock->last_update, current_time);
	if (clock->last_frame_time < 1.0)
		clock->time += clock->last_frame_time;
	clock->last_update = current_time;
}

static void		handle_input(t_window *win)
{
	t_keys *keys;
	t_mouse *mouse;
	t_mods *mods;
	uint32_t *state;

	keys = &win->keys;
	mouse = &win->mouse;
	mods = &win->mods;
	state = &win->game_state;

	if (keys->close.ended_down)
		close_hook(win);
	if ((*state & GS_TITLE) && keys->enter.changed && keys->enter.ended_down)
	{
		*state = GS_NORME;
		mods->update = 1;
	}
	if (keys->pause.ended_down && keys->pause.changed)
	{
		if (*state & GS_PAUSE)
		{
			*state = GS_NORME;
			nx_mouse_set_cursor_association(win->win, 0);
			nx_display_cursor(win->win, 0);
		}
		else if (*state & GS_NORME)
		{
			*state = GS_PAUSE;
			nx_mouse_set_cursor_association(win->win, 1);
			nx_display_cursor(win->win, 1);
		}
		mods->update = 1;
	}
	if (keys->up.ended_down && !keys->down.ended_down)
		mods->player_velocity = 50.0;
	else if (keys->up.changed)
		mods->player_velocity = 0.0;

	if (keys->down.ended_down && !keys->up.ended_down)
		mods->player_velocity = -50.0;
	else if (keys->down.changed)
		mods->player_velocity = 0.0;
	
	if (keys->up_arrow.ended_down && !keys->down_arrow.ended_down)
		mods->look_offset = 20.0;
	else if (keys->up_arrow.changed)
		mods->look_offset = 0.0;

	if (keys->down_arrow.ended_down && !keys->up_arrow.ended_down)
		mods->look_offset = -20.0;
	else if (keys->down_arrow.changed)
		mods->look_offset = 0.0;
	
	if (keys->left_alt.ended_down && !keys->right_alt.ended_down)
		mods->player_strafe_velocity = 20.0;
	else if (keys->left_alt.changed)
		mods->player_strafe_velocity = 0.0;

	if (keys->right_alt.ended_down && !keys->left_alt.ended_down)
		mods->player_strafe_velocity = -20.0;
	else if (keys->right_alt.changed)
		mods->player_strafe_velocity = 0.0;

	if (keys->left.ended_down && !keys->right.ended_down)
		mods->player_rotation_factor = -4;
	else if (keys->left.changed)
		mods->player_rotation_factor = 0;

	if (keys->right.ended_down && !keys->left.ended_down)
		mods->player_rotation_factor = 4;
	else if (keys->right.changed)
		mods->player_rotation_factor = 0;

/*	if (keys->fire.ended_down && keys->fire.changed)
		mods->should_fire = 1;
	else
		mods->should_fire = 0;
*/
	if (mouse->click1)
		mods->should_fire = 1;
	else
		mods->should_fire = 0;

	mods->player_angle = clamp_degrees_f(mods->player_angle);
	mods->update |= keys->up.ended_down
		| keys->down.ended_down
		| keys->left_alt.ended_down
		| keys->right_alt.ended_down
		| keys->left.ended_down
		| keys->right.ended_down
		//| (keys->fire.ended_down && keys->fire.changed)
		| keys->up_arrow.ended_down
		| keys->down_arrow.ended_down
		| (mouse->location.x != 0.0);

	if (*state & GS_PAUSE)
	{
		mods->player_velocity = 0.0;
		mods->look_offset = 0.0;
		mods->player_strafe_velocity = 0.0;
		mods->player_rotation_factor = 0.0;
	}
}

// 1: update time
// 2: handle input
// 3: update game state (determine if render needed)
// 4: render (if needed)

int32_t			main_loop(t_window *win)
{
	int32_t		needs_render;

	update_clock(&win->clock);
	handle_input(win);
	if (win->assets.gun.shooting_anim)
		needs_render = 1;
	if (win->is_initialized == 1)
	{
		if (win->game_state & GS_SPLASH)
			//render_splash(win);
			win->game_state = GS_TITLE;
/*		else*/ if (win->game_state & GS_TITLE)
			render_title(win);
		else if ((win->game_state & (GS_NORME | GS_PAUSE)) && win->mods.update)
			render_game(win);
		win->mods.update = 0;
	}
	reset_input(&win->keys, &win->mouse);
	return (0);
}

/*int32_t			main_loop(t_window *win)
{
	int32_t		needs_update;

	needs_update = handle_keys(&win->keys, &win->mods, win->game_state);
	if (win->keys.close.ended_down)
		close_hook(win);
	if ((win->game_state & GS_TITLE) && win->keys.enter.changed && win->keys.enter.ended_down)
	{
		win->game_state = GS_NORME;
		needs_update = 1;
	}
	if (win->keys.pause.ended_down && win->keys.pause.changed)
	{
		if (win->game_state & GS_PAUSE)
			win->game_state = GS_NORME;
		else if (win->game_state & GS_NORME)
			win->game_state = GS_PAUSE;
		needs_update = 1;
	}
	update_time(win);
	if (win->gun.shooting_anim)
		needs_update = 1;
	if (win->initialized == 1)
	{
		if (win->game_state & GS_SPLASH)
			//render_splash(win);
			win->game_state = GS_TITLE;
		if (win->game_state & GS_TITLE)
			render_title(win);
		else if ((win->game_state & (GS_NORME | GS_PAUSE)))
			render_game(win);
		win->mods.update = 0;
	}
	reset_key_changed(&win->keys);
	return (0);
}
*/
