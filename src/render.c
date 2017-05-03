#include <libft.h>
#include "fractal.h"
#include <mlx.h>
#include <math.h>


#include <stdio.h>

int32_t julia_frag(t_window *win, uint32_t x, uint32_t y)
{
     int32_t i;
     int32_t iterations;
     uint8_t r;
     uint8_t g;
     float coord_im;
     float coord_re;
     float zx;
     float zy;
     float zx2;
     float zy2;
     float squaredx;
     float squaredy;

     iterations = 15;
     coord_re = win->mods.xmouse * 2.0;
     coord_im = win->mods.ymouse * 2.0;
     r = 0;
     g = 255;
     i = 0;
     zx = (x - win->disp.width / 2.0) * (win->mods.scale / win->disp.width * win->disp.aspect_ratio);
     zy = (y - win->disp.height / 2.0) * (win->mods.scale / win->disp.height);
     squaredx = zx * zx;
     squaredy = zy * zy;
     while ((squaredx + squaredy) <= 4.0 && i < iterations)
     {
	  zx2 = zx;
	  zy2 = zy;
	  zx = zx2 * zx2 - zy2 * zy2 + coord_re;
	  zy = (zx2 + zx2) * zy2 + coord_im;
	  squaredx = zx * zx;
	  squaredy = zy * zy;
	  r += 16;
	  g -= 16;
	  ++i;
     }
     return ((int32_t)(255 | g << 8 | r << 16));
}

int32_t mandelbrot_frag(t_window *win, uint32_t x, uint32_t y)
{
     int32_t i;
     int32_t iterations;
     uint8_t r;
     uint8_t g;
     float coord_im;
     float coord_re;
     float zx;
     float zy;
     float zx2;
     float zy2;
     float squaredx;
     float squaredy;

     iterations = 15;
     coord_re = (x - win->disp.width / 2.0) * (win->mods.scale / win->disp.width * win->disp.aspect_ratio);
     coord_im = (y - win->disp.height / 2.0) * (win->mods.scale / win->disp.height);
     r = 0;
     g = 255;
     i = 0;
     zx = 0;
     zy = 0;
     squaredx = zx * zx;
     squaredy = zy * zy;
     while ((squaredx + squaredy) <= 4.0 && i < iterations)
     {
	  zx2 = zx;
	  zy2 = zy;
	  zx = zx2 * zx2 - zy2 * zy2 + coord_re;
	  zy = (zx2 + zx2) * zy2 + coord_im;
	  squaredx = zx * zx;
	  squaredy = zy * zy;
	  r += 16;
	  g -= 16;
	  ++i;
     }
     return ((int32_t)(255 | g << 8 | r << 16));
}

int32_t burning_ship_frag(t_window *win, uint32_t x, uint32_t y)
{
     int32_t i;
     int32_t iterations;
     uint8_t r;
     uint8_t g;
     float coord_im;
     float coord_re;
     float zx;
     float zy;
     float squaredx;
     float squaredy;

     iterations = 15;
     coord_re = (x - win->disp.width / 2.0) * (win->mods.scale / win->disp.width * win->disp.aspect_ratio);
     coord_im = (y - win->disp.height / 2.0) * (win->mods.scale / win->disp.height);
     r = 0;
     g = 255;
     i = 0;
     zx = coord_re;
     zy = coord_im;
     squaredx = zx * zx;
     squaredy = zy * zy;
     while ((squaredx + squaredy) <= 4.0 && i < iterations)
     {
	  zy = ABS(zx * zy);
	  zy = zy + zy - coord_im;
	  zx = squaredx - squaredy + coord_re;
	  squaredx = zx * zx;
	  squaredy = zy * zy;
	  r += 16;
	  g -= 16;
	  ++i;
     }
     return ((int32_t)(255 | g << 8 | r << 16));
}

void render(t_window *win)
{
     int32_t *buffer;
     size_t k;
     uint32_t x;
     uint32_t y;

     buffer = (int32_t *)win->disp.data;
     k = 0;
     while (k < win->disp.size_line / sizeof(int32_t) * win->disp.height)
     {
	  // render different fractals
	  x = (uint32_t)(k % win->disp.width);
	  y = win->disp.height - (uint32_t)(k / win->disp.width);
//color = render_julia(win, buffer, x, y);
//color = render_mandelbrot(win, buffer, x, y);
	  buffer[k] = julia_frag(win, x, y);
	  ++k;
     }
     mlx_put_image_to_window(win->mlx, win->win, win->disp.ptr,
			     win->center.x - win->disp.center.x,
			     win->center.y - win->disp.center.y);
}
