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

     iterations = 64;
     coord_re = win->mods.xmouse * 2.0;
     coord_im = win->mods.ymouse * 2.0;
     i = 0;
     zr = win->mods.xoffset + (x - (float)win->disp.center.x) * win->mods.scale;
     zi = win->mods.yoffset + (y - (float)win->disp.center.y) * win->mods.scale;
     //zr = (x - win->disp.width / 2.0) * (win->mods.scale / win->disp.width * win->disp.aspect_ratio);
     //zi = (y - win->disp.height / 2.0) * (win->mods.scale / win->disp.height);
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

     iterations = 64;
     coord_re = win->mods.xoffset + (x - (float)win->disp.center.x) * win->mods.scale;
     coord_im = win->mods.yoffset + (y - (float)win->disp.center.y) * win->mods.scale;
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
     double zr;
     double zi;
     double squaredr;
     double squaredi;

     iterations = 64;
     //ax = cx + x * scale;
     //ay = cy + y * scale;
//     coord_re = (x - (float)win->disp.center.x) * (win->mods.scale / win->disp.width * win->disp.aspect_ratio);
//     coord_im = (y - (float)win->disp.center.y) * (win->mods.scale / win->disp.height);
     coord_re = win->mods.xoffset + (x - (float)win->disp.center.x) * win->mods.scale;
     coord_im = win->mods.yoffset + (y - (float)win->disp.center.y) * win->mods.scale;
     //    printf("%f %f %f %f\n", coord_re, coord_im, win->mods.xoffset, win->mods.yoffset);
     i = 0;
     zr = coord_re;
     zi = coord_im;
     squaredr = square(zr);
     squaredi = square(zi);
     while ((squaredr + squaredi) <= 4.0 && i < iterations)
     {
	  zi = ABS(zr * zi);
	  zi = zi + zi - coord_im;
	  zr = squaredr - squaredi + coord_re;
	  squaredr = square(zr);
	  squaredi = square(zi);
	  ++i;
     }
     return (color_arr[i % 4]);
}

void render_gpu(t_window *win)
{
     int32_t *buffer;
     int result[DATA_SIZE];
     size_t global;
     uint32_t count;
     int err;
     
     buffer = (int32_t *)win->disp.data;
     count = DATA_SIZE;
     err = 0;
     int w = win->disp.width;
     int h = win->disp.height;
     double scale = win->mods.scale;
     double aspect = win->disp.aspect_ratio;
     double xmouse = win->mods.xmouse;
     double ymouse = win->mods.ymouse;
     err |= clSetKernelArg(win->cl.kernel, 0, sizeof(cl_mem), &win->cl.output);
     err |= clSetKernelArg(win->cl.kernel, 1, sizeof(unsigned int), &count);
     err |= clSetKernelArg(win->cl.kernel, 2, sizeof(int), &w);
     err |= clSetKernelArg(win->cl.kernel, 3, sizeof(int), &h);
     err |= clSetKernelArg(win->cl.kernel, 4, sizeof(double), &scale);
     err |= clSetKernelArg(win->cl.kernel, 5, sizeof(double), &aspect);
     err |= clSetKernelArg(win->cl.kernel, 6, sizeof(double), &xmouse);
     err |= clSetKernelArg(win->cl.kernel, 7, sizeof(double), &ymouse);
 
     if (err != CL_SUCCESS)
	  exit(1);

     global = count;
     err = clEnqueueNDRangeKernel(win->cl.commands, win->cl.kernel, 1, NULL, &global, &win->cl.local, 0, NULL, NULL);
     if (err)
	  exit(1);

     clFinish(win->cl.commands);
     
     err = clEnqueueReadBuffer(win->cl.commands, win->cl.output, CL_TRUE, 0, sizeof(int) * count, result, 0, NULL, NULL );  
     if (err != CL_SUCCESS)
     {
	  printf("Error: Failed to read output array! %d\n", err);
	  exit(1);
     }
     for (size_t b = 0; b < count; b++)
     {
	  buffer[b] = color_arr[result[b]];
     }
     mlx_put_image_to_window(win->mlx, win->win, win->disp.ptr,
			     win->center.x - win->disp.center.x,
			     win->center.y - win->disp.center.y);
}

void render_normal(t_window *win)
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
	  if (win->opts & OPT_SHIP)
	       buffer[k] = burning_ship_frag(win, x, y);
	  else if (win->opts & OPT_JULIA)
	       buffer[k] = julia_frag(win, x, y);
	  else if (win->opts & OPT_MANDELBROT)
	       buffer[k] = mandelbrot_frag(win, x, y);
	  ++k;
     }
     mlx_put_image_to_window(win->mlx, win->win, win->disp.ptr,
			     win->center.x - win->disp.center.x,
			     win->center.y - win->disp.center.y);
}

void render (t_window *win)
{
     if (win->opts & OPT_GPU)
	  render_gpu(win);
     else
	  render_normal(win);
}
