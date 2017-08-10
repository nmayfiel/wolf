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

#include <libft.h>
#include "wolf.h"
#include <stdlib.h>
#include <mlx.h>
#include <mach/mach_time.h>

#include <stdio.h>


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
	keys->enter.changed = 0;
	keys->pause.changed = 0;
	keys->right_alt.changed = 0;
	keys->left_alt.changed = 0;
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

uint32_t handle_pause(uint32_t state, void *winptr)
{
	uint32_t new_state;

	new_state = state;
	if (state & GS_PAUSE)
	{
		new_state = GS_NORME;
		nx_mouse_set_cursor_association(winptr, 0);
		nx_display_cursor(winptr, 0);
	}
	else if (state & GS_NORME)
	{
		new_state = GS_PAUSE;
		nx_mouse_set_cursor_association(winptr, 1);
		nx_display_cursor(winptr, 1);
	}
	return (new_state);
}

void handle_movement_keys(t_keys *keys, t_mods *mods)
{
	if (keys->up.ended_down && !keys->down.ended_down)
		mods->player_velocity = 50.0;
	else if (keys->up.changed)
		mods->player_velocity = 0.0;
	if (keys->down.ended_down && !keys->up.ended_down)
		mods->player_velocity = -50.0;
	else if (keys->down.changed)
		mods->player_velocity = 0.0;
	if (keys->left_alt.ended_down && !keys->right_alt.ended_down)
		mods->player_strafe_velocity = 20.0;
	else if (keys->left_alt.changed)
		mods->player_strafe_velocity = 0.0;
	if (keys->right_alt.ended_down && !keys->left_alt.ended_down)
		mods->player_strafe_velocity = -20.0;
	else if (keys->right_alt.changed)
		mods->player_strafe_velocity = 0.0;
}


static void		handle_input(t_keys *keys, t_mouse *mouse, t_mods *mods, t_window *win)
{
	if (keys->close.ended_down)
		close_hook(win);
	if ((win->game_state & GS_TITLE) && keys->enter.changed && keys->enter.ended_down)
		win->game_state = GS_NORME;
	if (keys->pause.ended_down && keys->pause.changed)
		win->game_state = handle_pause(win->game_state, win->win);
	handle_movement_keys(keys, mods);
	if (mouse->click1)
		mods->should_fire = 1;
	else
		mods->should_fire = 0;
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
//			if (update_game(win, win->clock.last_frame_time))
				render_game(win);
		}
		else if (win->game_state & GS_PAUSE)
		{
			if (win->keys.pause.changed)
				render_game(win);
		}
	}
	reset_input(&win->keys, &win->mouse);
	return (0);
}
