#include "keys.h"
#include <stdint.h>

int32_t		add_key(int32_t keycode, t_keys *keys)
{
	if (!keys)
		return (0);
	if (keycode == KEY_ESC)
		*keys = *keys ^ KVAL_ESC;
	else if (keycode == KEY_UP)
		*keys = *keys ^ KVAL_UP;
	else if (keycode == KEY_LEFT)
		*keys = *keys ^ KVAL_LEFT;
	else if (keycode == KEY_DOWN)
		*keys = *keys ^ KVAL_DOWN;
	else if (keycode == KEY_RIGHT)
		*keys = *keys ^ KVAL_RIGHT;
	else if (keycode == KEY_Q)
		*keys = *keys ^ KVAL_Q;
	else if (keycode == KEY_E)
		*keys = *keys ^ KVAL_E;
	else if (keycode == KEY_W)
		*keys = *keys ^ KVAL_W;
	else if (keycode == KEY_A)
		*keys = *keys ^ KVAL_A;
	else if (keycode == KEY_S)
		*keys = *keys ^ KVAL_S;
	else if (keycode == KEY_D)
		*keys = *keys ^ KVAL_D;
	else if (keycode == KEY_I)
		*keys = *keys ^ KVAL_I;
	else if (keycode == KEY_J)
		*keys = *keys ^ KVAL_J;
	else if (keycode == KEY_K)
		*keys = *keys ^ KVAL_K;
	else if (keycode == KEY_L)
		*keys = *keys ^ KVAL_L;
	return (0);
}

int32_t		remove_key(int32_t keycode, t_keys *keys)
{
	if (!keys)
		return (0);
	if (keycode == KEY_ESC)
		*keys |= KVAL_ESC;
	else if (keycode == KEY_UP)
		*keys |= KVAL_UP;
	else if (keycode == KEY_LEFT)
		*keys |= KVAL_LEFT;
	else if (keycode == KEY_DOWN)
		*keys |= KVAL_DOWN;
	else if (keycode == KEY_RIGHT)
		*keys |= KVAL_RIGHT;
	else if (keycode == KEY_Q)
		*keys |= KVAL_Q;
	else if (keycode == KEY_E)
		*keys |= KVAL_E;
	else if (keycode == KEY_W)
		*keys |= KVAL_W;
	else if (keycode == KEY_A)
		*keys |= KVAL_A;
	else if (keycode == KEY_S)
		*keys |= KVAL_S;
	else if (keycode == KEY_D)
		*keys |= KVAL_D;
	else if (keycode == KEY_I)
		*keys |= KVAL_I;
	else if (keycode == KEY_J)
		*keys |= KVAL_J;
	else if (keycode == KEY_K)
		*keys |= KVAL_K;
	else if (keycode == KEY_L)
		*keys |= KVAL_L;
	return (0);
}
