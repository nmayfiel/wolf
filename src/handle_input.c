#include "wolf.h"
#include <mlx.h>

static uint32_t handle_pause(uint32_t state, void *winptr)
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

static void handle_movement_keys(t_keys *keys, t_mods *mods)
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


void		handle_input(t_keys *keys, t_mouse *mouse, t_mods *mods, t_window *win)
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
