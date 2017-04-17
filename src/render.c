#include <libft.h>
#include "fractal.h"
#include <mlx.h>
#include <math.h>


#include <stdio.h>

/*
** TODO: Put this in a Mandelbrot function
** you will declare a variable and check it
** to see which type of fractal you want to display,
** remember mandelbrot and julia and a third of your
** choice are required
*/

void render(t_window *win)
{
     int32_t *buffer;
     int32_t iteration;
     int32_t iterations;
     size_t i;
     uint8_t r;
     uint8_t b;

     buffer = (int32_t *)win->disp.data;
     i = 0;
     iterations = 16;
     while (i < win->disp.size_line / sizeof(int32_t) * win->disp.height)
     {
	  uint32_t col = (uint32_t)(i % win->disp.width);
	  uint32_t row = (uint32_t)(i / win->disp.width);

	  double c_re = (col - win->disp.width / 2.0) * win->mods.scale / win->disp.width;
	  double c_im = (row - win->disp.height / 2.0) * win->mods.scale / win->disp.width;
	  double x = 0, y = 0;
	  iteration = 0;
	  r = 0;
	  b = 255;
	  while (x * x + y * y <= 4 && iteration < iterations)
	  {
	       double x_new = x*x - y*y + c_re;
	       y = 2*x*y + c_im;
	       x = x_new;
	       r += 16;
	       b -= 16;
	       ++iteration;
	  }
	  buffer[i] = 255 | b << 8 | r << 16;
	  ++i;
     }
     mlx_put_image_to_window(win->mlx, win->win, win->disp.ptr,
			     win->center.x - win->disp.center.x,
			     win->center.y - win->disp.center.y);
}
