#include <libft.h>
#include "fractal.h"
#include "keys.h"
#include <stdlib.h>
#include <stdio.h>
#include <mlx.h>

int32_t close_hook(t_window *win)
{
     mlx_destroy_window(win->mlx, win->win);
     exit(0);
}

/*
** handle_keys
** arguments: t_keys bit field, fields to modify
** 
** checks which key bits are flipped,
** and adjusts the appropriate value
**
** return value: 1 or 0 depending on whether keys were
** pressed or not
*/

static int32_t handle_keys(t_keys keys/*, t_mods *mods*/)
{
     return (keys != 0);
}


int32_t main_loop(t_window *win)
{
     static int32_t rendered_once = 0;
     int32_t update;

     win->time += 0.01;
     if (win->keys & KVAL_ESC)
	  close_hook(win);
     if (win->initialized == 1 && win->time >= 2.0)
     {
	  update = handle_keys(win->keys/*, &win->mods*/);
	  if (!rendered_once || update)
	       render(win);
	  rendered_once = 1;
     }
     else
	  render_splash(win);
     return (0);
}
