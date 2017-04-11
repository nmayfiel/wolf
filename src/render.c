#include <libft.h>
#include "fractal.h"
#include <mlx.h>
#include <math.h>

void render(t_window *win)
{
     // Rendering code goes here.
     mlx_put_image_to_window(win->mlx, win->win, win->splash.ptr,
			     win->center.x - win->splash.center.x,
			     win->center.y - win->splash.center.y);
}
