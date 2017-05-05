#include <libft.h>
#include "fractal.h"
#include "keys.h"
#include <stdlib.h>
#include <stdio.h>
#include <mlx.h>

int32_t close_hook(t_window *win)
{
     mlx_destroy_window(win->mlx, win->win);
     if (win->opts & OPT_GPU)
	  release_cl_device(&win->cl);
     exit(0);
}

static int32_t handle_keys(t_keys keys, t_mods *mods)
{
     if (keys & KVAL_UP)
	  mods->yoffset -= mods->scale * 11;
     if (keys & KVAL_DOWN)
	  mods->yoffset += mods->scale * 11;
     if (keys & KVAL_LEFT)
	  mods->xoffset += mods->scale * 11;
     if (keys & KVAL_RIGHT)
	  mods->xoffset -= mods->scale * 11;
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
	  update = handle_keys(win->keys, &win->mods);
	  if (!rendered_once || update || win->mods.update)
	       render(win);
	  win->mods.update = 0;
	  rendered_once = 1;
     }
     else
	  render_splash(win);
     return (0);
}
