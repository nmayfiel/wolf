#include <libft.h>
#include "fractol.h"
#include <mlx.h>
#include <math.h>


#include <stdio.h>

float	square(double x)
{
	return (x * x);
}

typedef struct	s_double2
{
	double x;
	double y;
}				t_double2;

const int32_t color_arr[2][32] = { {0x00003F0B, 0x00006512, 0x00007F16, 0x00008C18, 0x0000CB23, 0x00008C18, 0x00007F16,  0x00006512, 0x00003F0B, 0x00003F0B, 0x00035E5E, 0x00047878, 0x00048585, 0x0007C4C4, 0x00048585, 0x00047878, 0x00035E5E, 0x00003F0B, 0x00402E0D, 0x007F5B19, 0x00BF8926, 0x00E5A52E, 0x00FFB733, 0x00E5A52E, 0x00BF8926,  0x007F5B19, 0x00402E0D, 0x00821616, 0x00A81D1D, 0x00C22121, 0x00A81D1D, 0x00420B0B}, {0x00000000, 0x00BBBBBB, 0x00000000, 0x00BBBBBB, 0x00000000, 0x00BBBBBB, 0x00000000, 0x00BBBBBB, 0x00000000, 0x00BBBBBB, 0x00000000, 0x00BBBBBB, 0x00000000, 0x00BBBBBB, 0x00000000, 0x00BBBBBB, 0x00000000, 0x00BBBBBB, 0x00000000, 0x00BBBBBB, 0x00000000, 0x00BBBBBB, 0x00000000, 0x00BBBBBB, 0x00000000, 0x00BBBBBB, 0x00000000, 0x00BBBBBB, 0x00000000, 0x00BBBBBB, 0x00000000, 0x00BBBBBB}};
const int32_t num_colors = 32;

int32_t	julia_frag(t_window *win, uint32_t x, uint32_t y)
{
	int32_t i;
	t_double2 coord;
	t_double2 z;
	t_double2 squared;

	//double coord_im;
	//double coord_re;
	//double zr;
	//double zi;
	//double squaredr;
	//double squaredi;

	coord.x = win->mods.xmouse * 2.0;
	coord.y = win->mods.ymouse * 2.0;
	i = 0;
	z.x = win->mods.xoffset + (x - (double)win->disp.center.x) * win->mods.scale;
	z.y = win->mods.yoffset + (y - (double)win->disp.center.y) * win->mods.scale;
	squared.x = square(z.x);
	squared.y = square(z.y);
	while (squared.x + squared.y <= 4.0 && i < win->mods.iterations)
	{
		z.y = square(z.x + z.y) - squared.x - squared.y + coord.y;
		z.x = squared.x - squared.y + coord.x;
		squared.x = square(z.x);
		squared.y = square(z.y);
		++i;
	}
	return (color_arr[win->mods.color_index][i % num_colors]);
}

int32_t	mandelbrot_frag(t_window *win, uint32_t x, uint32_t y)
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
	coord_re = win->mods.xoffset + (x - (double)win->disp.center.x) * win->mods.scale;
	coord_im = win->mods.yoffset + (y - (double)win->disp.center.y) * win->mods.scale;
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
	return (color_arr[win->mods.color_index][i % num_colors]);
}

int32_t	burning_ship_frag(t_window *win, uint32_t x, uint32_t y)
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
	coord_re = win->mods.xoffset + (x - (double)win->disp.center.x) * win->mods.scale;
	coord_im = win->mods.yoffset + (y - (double)win->disp.center.y) * win->mods.scale;
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
	return (color_arr[win->mods.color_index][i % num_colors]);
}

void	render_gpu(t_window *win)
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
	float scale = win->mods.scale;
	float xmouse = win->mods.xmouse;
	float ymouse = win->mods.ymouse;
	float xoffset = win->mods.xoffset;
	float yoffset = win->mods.yoffset;
	int iterations = win->mods.iterations;
	int num_col = num_colors;
	err |= clSetKernelArg(win->cl.kernel, 0, sizeof(cl_mem), &win->cl.output);
	err |= clSetKernelArg(win->cl.kernel, 1, sizeof(unsigned int), &count);
	err |= clSetKernelArg(win->cl.kernel, 2, sizeof(int), &w);
	err |= clSetKernelArg(win->cl.kernel, 3, sizeof(int), &h);
	err |= clSetKernelArg(win->cl.kernel, 4, sizeof(double), &scale);
	err |= clSetKernelArg(win->cl.kernel, 5, sizeof(double), &xmouse);
	err |= clSetKernelArg(win->cl.kernel, 6, sizeof(double), &ymouse);
	err |= clSetKernelArg(win->cl.kernel, 7, sizeof(double), &xoffset);
	err |= clSetKernelArg(win->cl.kernel, 8, sizeof(double), &yoffset);
	err |= clSetKernelArg(win->cl.kernel, 9, sizeof(int), &iterations);
	err |= clSetKernelArg(win->cl.kernel, 10, sizeof(int), &num_col);
	if (err != CL_SUCCESS)
	{
		printf("Could not set arguments for opencl\n");
		exit(1);
	}
	global = count;
	err = clEnqueueNDRangeKernel(win->cl.commands, win->cl.kernel, 1, NULL, &global, &win->cl.local, 0, NULL, NULL);
	if (err)
	{
		printf("Could not enqueue kernel\n");
		exit(1);
	}
	clFinish(win->cl.commands);
	err = clEnqueueReadBuffer(win->cl.commands, win->cl.output, CL_TRUE, 0, sizeof(int) * count, result, 0, NULL, NULL );  
	if (err != CL_SUCCESS)
	{
		printf("Error: Failed to read output array! %d\n", err);
		exit(1);
	}
	for (size_t b = 0; b < count; b++)
	{
		buffer[b] = color_arr[win->mods.color_index][result[b]];
	}
	mlx_put_image_to_window(win->mlx, win->win, win->disp.ptr,
			win->center.x - win->disp.center.x,
			win->center.y - win->disp.center.y);
}

void	render_normal(t_window *win)
{
	int32_t *buffer;
	size_t k;
	uint32_t x;
	uint32_t y;

	buffer = (int32_t *)win->disp.data;
	k = 0;
	while (k < win->disp.size_line / sizeof(int32_t) * win->disp.height)
	{
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

void	render(t_window *win)
{
	if (win->opts & OPT_GPU)
		render_gpu(win);
	else
		render_normal(win);
	mlx_string_put(win->mlx, win->win, WIN_WIDTH - 120, WIN_HEIGHT - 30, 0x00EEEEEE, "Iter:");
	mlx_string_put(win->mlx, win->win, WIN_WIDTH - 60, WIN_HEIGHT - 30, 0x00FFFFFF, ft_itoa(win->mods.iterations));
	mlx_string_put(win->mlx, win->win, WIN_WIDTH - 120, WIN_HEIGHT - 50, 0x00FFFFFF, "Zoom:");
	mlx_string_put(win->mlx, win->win, WIN_WIDTH - 60, WIN_HEIGHT - 50, 0x00FFFFFF, ft_itoa((int)(-log( win->mods.scale))));
	mlx_string_put(win->mlx, win->win, WIN_WIDTH - 120, WIN_HEIGHT - 90, 0x00EEEEEE, "XOff:");
	mlx_string_put(win->mlx, win->win, WIN_WIDTH - 60, WIN_HEIGHT - 90, 0x00FFFFFF, ft_itoa((int)win->mods.xoffset));
	mlx_string_put(win->mlx, win->win, WIN_WIDTH - 120, WIN_HEIGHT - 70, 0x00EEEEEE, "YOff:");
	mlx_string_put(win->mlx, win->win, WIN_WIDTH - 60, WIN_HEIGHT - 70, 0x00FFFFFF, ft_itoa((int)win->mods.yoffset));
}
