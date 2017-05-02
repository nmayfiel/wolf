#include <libft.h>
#include "fractal.h"
#include <mlx.h>
#include <math.h>


#include <stdio.h>

// TODO: Heavy refactoring needed in this file

void render(t_window *win)
{
     int32_t *buff;
     int32_t i;
     int32_t iterations;
     size_t k;
     uint8_t r;
     uint8_t g;

     //float cRe = -0.7;
     //float cIm = 0.27015;
     float cRe = win->mods.xmouse;
     float cIm = win->mods.ymouse;
     float oldIm;
     float oldRe;
     float newIm;
     float newRe;
     buff = (int32_t *)win->disp.data;
     k = 0;
     iterations = 255;
     float aspect = (float)win->disp.width / (float)win->disp.height;
     while (k < win->disp.size_line / sizeof(int32_t) * win->disp.height)
     {
	  uint32_t x = (uint32_t)(k % win->disp.width);
	  uint32_t y = (uint32_t)(k / win->disp.width);
	  newRe = (x - win->disp.width / 2.0) * (win->mods.scale / win->disp.width * aspect);
	  newIm = (y - win->disp.height / 2.0) * (win->mods.scale / win->disp.height);
	  r = 0;
	  g = 255;
	  i = 0;
	  while ((newRe * newRe + newIm * newIm) <= 4.0 && i < iterations)
	  {
	       oldRe = newRe;
	       oldIm = newIm;
	       newRe = oldRe * oldRe - oldIm * oldIm + cRe;
	       newIm = 2 * oldRe * oldIm + cIm;
	       r += 1;
	       g -= 1;
	       ++i;
	  }
	  buff[k] = 255 | g << 8 | r << 16;
	  ++k;
     }
     mlx_put_image_to_window(win->mlx, win->win, win->disp.ptr,
			     win->center.x - win->disp.center.x,
			     win->center.y - win->disp.center.y);
}

void render_manelbrot(t_window *win)
{
     int32_t *buff;
     int32_t i;
     int32_t iterations;
     size_t k;
     uint8_t r;
     uint8_t g;
     float oldIm;
     float oldRe;
     float newIm;
     float newRe;
     float cIm;
     float cRe;

     buff = (int32_t *)win->disp.data;
     k = 0;
     iterations = 15;
     float aspect = (float)win->disp.width / (float)win->disp.height;
     while (k < win->disp.size_line / sizeof(int32_t) * win->disp.height)
     {
	  uint32_t x = (uint32_t)(k % win->disp.width);
	  uint32_t y = (uint32_t)(k / win->disp.width);
	  cRe = (x - win->disp.width / 2.0) * (win->mods.scale / win->disp.width * aspect);
	  cIm = (y - win->disp.height / 2.0) * (win->mods.scale / win->disp.height);
	  newRe = 0;
	  newIm = 0;
	  r = 0;
	  g = 255;
	  i = 0;
	  while ((newRe * newRe + newIm * newIm) <= 4.0 && i < iterations)
	  {
	       oldRe = newRe;
	       oldIm = newIm;
	       newRe = oldRe * oldRe - oldIm * oldIm + cRe;
	       newIm = 2 * oldRe * oldIm + cIm;
	       r += 16;
	       g -= 16;
	       ++i;
	  }
	  buff[k] = 255 | g << 8 | r << 16;
	  ++k;
     }
     mlx_put_image_to_window(win->mlx, win->win, win->disp.ptr,
			     win->center.x - win->disp.center.x,
			     win->center.y - win->disp.center.y);
}

void render_burning_ship(t_window *win)
{
     int32_t *buff;
     int32_t i;
     int32_t iterations;
     size_t k;
     uint8_t r;
     uint8_t g;
     float newIm;
     float newRe;
     float cIm;
     float cRe;

     buff = (int32_t *)win->disp.data;
     k = 0;
     iterations = 15;
     float aspect = (float)win->disp.width / (float)win->disp.height;
     while (k < win->disp.size_line / sizeof(int32_t) * win->disp.height)
     {
	  uint32_t x = (uint32_t)(k % win->disp.width);
	  uint32_t y = win->disp.height - (uint32_t)(k / win->disp.width);
	  cRe = (x - win->disp.width / 2.0) * (win->mods.scale / win->disp.width * aspect);
	  cIm = (y - win->disp.height / 2.0) * (win->mods.scale / win->disp.height);
	  newRe = 0;
	  newIm = 0;
	  r = 0;
	  g = 255;
	  i = 0;
	  float zx = cRe;
	  float zy = cIm;
	  float squaredx = zx * zx;
	  float squaredy = zy * zy;
	  while ((squaredx + squaredy) <= 4.0 && i < iterations)
	  {
	       zy = ABS(zx * zy);
	       zy = zy + zy - cIm;
	       zx = squaredx - squaredy + cRe;
	       squaredx = zx * zx;
	       squaredy = zy * zy;
	       r += 16;
	       g -= 16;
	       ++i;
	  }
	  buff[k] = 255 | g << 8 | r << 16;
	  ++k;
     }
     mlx_put_image_to_window(win->mlx, win->win, win->disp.ptr,
			     win->center.x - win->disp.center.x,
			     win->center.y - win->disp.center.y);
}
