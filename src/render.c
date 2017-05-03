#include <libft.h>
#include "fractal.h"
#include <mlx.h>
#include <math.h>


#include <stdio.h>

float square(float x)
{
     return (x * x);
}

const int32_t color_arr[4] = {0x00000000, 0x00AAAAAA, 0x00000000, 0x00AAAAAA};

int32_t julia_frag(t_window *win, uint32_t x, uint32_t y)
{
     int32_t i;
     int32_t iterations;
     double coord_im;
     double coord_re;
     double zr;
     double zi;
     double squaredr;
     double squaredi;

     iterations = 32;
     /*coord_re = win->mods.xmouse * 2.0;
     coord_im = win->mods.ymouse * 2.0;
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
	  ++i;
	  }*/

     coord_re = win->mods.xmouse * 2.0;
     coord_im = win->mods.ymouse * 2.0;
     i = 0;
     zr = (x - win->disp.width / 2.0) * (win->mods.scale / win->disp.width * win->disp.aspect_ratio);
     zi = (y - win->disp.height / 2.0) * (win->mods.scale / win->disp.height);
     squaredr = square(zr);
     squaredi = square(zi);
     while (squaredr + squaredi <= 4.0 && i < iterations)
     {
	  zi = square(zr + zi) - squaredr - squaredi + coord_im;
	  zr = squaredr - squaredi + coord_re;
	  squaredr = square(zr);
	  squaredi = square(zi);
	  ++i;
     }
     return (color_arr[i % 4]);
}

/// TODO: Use the loop in mandelbrot frag in your julia,
/// change the names of variables to match this one...

int32_t mandelbrot_frag(t_window *win, uint32_t x, uint32_t y)
{
     int32_t i;
     int32_t iterations;
     float coord_im;
     float coord_re;
     float zr;
     float zi;
     float squaredr;
     float squaredi;

     iterations = 255;
     coord_re = (x - win->disp.width / 2.0) * (win->mods.scale / win->disp.width * win->disp.aspect_ratio);
     coord_im = (y - win->disp.height / 2.0) * (win->mods.scale / win->disp.height);
     i = 0;
     zr = 0;
     zi = 0;
     squaredr = square(zr);
     squaredi = square(zi);
     while ((squaredr + squaredi) <= 4.0 && i < iterations)
     {
	  zi = square(zr + zi) - squaredr - squaredi + coord_im;
	  zr = squaredr - squaredi + coord_re;
	  squaredr = square(zr);
	  squaredi = square(zi);
	  ++i;
     }
     return (color_arr[i % 4]);
}

int32_t burning_ship_frag(t_window *win, uint32_t x, uint32_t y)
{
     int32_t i;
     int32_t iterations;
     double coord_im;
     double coord_re;
     double zx;
     double zy;
     double squaredx;
     double squaredy;

     iterations = 100;
     coord_re = (x - win->disp.width / 2.0) * (win->mods.scale / win->disp.width * win->disp.aspect_ratio) + win->mods.xoffset;
     coord_im = (y - win->disp.height / 2.0) * (win->mods.scale / win->disp.height) + win->mods.yoffset;
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
	  ++i;
     }
     return (color_arr[i % 4]);
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
	  buffer[k] = burning_ship_frag(win, x, y);
	  //buffer[k] = julia_frag(win, x, y);
	  //buffer[k] = mandelbrot_frag(win, x, y);
	  ++k;
     }
     mlx_put_image_to_window(win->mlx, win->win, win->disp.ptr,
			     win->center.x - win->disp.center.x,
			     win->center.y - win->disp.center.y);
}
