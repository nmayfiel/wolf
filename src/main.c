/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 17:23:55 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/05/03 20:10:46 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/opencl.h>
#include "fractal.h"
#include "keys.h"
#include <libft.h>
#include <mlx.h>
#include <stdlib.h>

#include <stdio.h>

const char *burning_ship_source = "\n" \
"__kernel void burning_ship_kernel(                                     \n" \
"   __global int *output,                                               \n" \
"   const unsigned int count,                                           \n" \
"   int width,                                                    \n" \
"   int height,                                                   \n" \
"   float scale,                                                  \n" \
"   float aspect)                                                 \n" \
"{                                                                      \n" \
"   int k = get_global_id(0);                                           \n" \
"   if(k < count){                                                      \n" \
"       int x = k % width;                                              \n" \
"       int y = height - (k / width);                                   \n" \
"       float coord_re = (x - width / 2.0f) * (scale / width * aspect); \n" \
"       float coord_im = (y - height / 2.0f) * (scale / height);        \n" \
"       float zr = coord_re;                                            \n" \
"       float zi = coord_im;                                            \n" \
"       float squaredr = zr * zr;                                       \n" \
"       float squaredi = zi * zi;                                       \n" \
"       int i = 0;                                                      \n" \
"       while (squaredr + squaredi <= 4.0f && i < 2048){                  \n" \
"           zi = zr * zi;                                               \n" \
"           if(zi < 0)                                                  \n" \
"               zi = -zi;                                               \n" \
"           zi = zi + zi - coord_im;                                    \n" \
"           zr = squaredr - squaredi + coord_re;                        \n" \
"           squaredr = zr * zr;                                         \n" \
"           squaredi = zi * zi;                                         \n" \
"           ++i;                                                        \n" \
"       }                                                               \n" \
"       output[k] = i % 4;                                              \n" \
"   }                                                                   \n" \
"}                                                                      \n" \
"\n";

const char *julia_source = "\n" \
"__kernel void julia_kernel(                                     \n" \
"   __global int *output,                                               \n" \
"   const unsigned int count,                                           \n" \
"   int width,                                                    \n" \
"   int height,                                                   \n" \
"   double scale,                                                  \n" \
"   double aspect,                                                 \n" \
"   double mousex,                                                 \n" \
"   double mousey)                                                 \n" \
"{                                                                      \n" \
"   int k = get_global_id(0);                                           \n" \
"   if(k < count){                                                      \n" \
"       int x = k % width;                                              \n" \
"       int y = height - (k / width);                                   \n" \
"       double coord_im = mousex * 2.0f;                                 \n" \
"       double coord_re = mousey * 2.0f;                                 \n" \
"       double zr = (x - width / 2.0f) * (scale / width * aspect);       \n" \
"       double zi = (y - height / 2.0f) * (scale / height);              \n" \
"       double squaredr = zr * zr;                                       \n" \
"       double squaredi = zi * zi;                                       \n" \
"       int i = 0;                                                      \n" \
"       while (squaredr + squaredi <= 4.0f && i < 4096){                  \n" \
"           zi = (zr + zi) * (zr + zi) - squaredr - squaredi + coord_im;  \n" \
"           zr = squaredr - squaredi + coord_re;                        \n" \
"           squaredr = zr * zr;                                         \n" \
"           squaredi = zi * zi;                                         \n" \
"           ++i;                                                        \n" \
"       }                                                               \n" \
"       output[k] = i % 4;                                              \n" \
"   }                                                                   \n" \
"}                                                                      \n" \
"\n";


const char *mandelbrot_source = "\n" \
"__kernel void mandelbrot_kernel(                                     \n" \
"   __global int *output,                                               \n" \
"   const unsigned int count,                                           \n" \
"   int width,                                                    \n" \
"   int height,                                                   \n" \
"   float scale,                                                  \n" \
"   float aspect)                                                 \n" \
"{                                                                      \n" \
"   int k = get_global_id(0);                                           \n" \
"   if(k < count){                                                      \n" \
"       int x = k % width;                                              \n" \
"       int y = height - (k / width);                                   \n" \
"       float coord_re = (x - width / 2.0f) * (scale / width * aspect); \n" \
"       float coord_im = (y - height / 2.0f) * (scale / height);        \n" \
"       float zr = 0;                                            \n" \
"       float zi = 0;                                            \n" \
"       float squaredr = zr * zr;                                       \n" \
"       float squaredi = zi * zi;                                       \n" \
"       int i = 0;                                                      \n" \
"       while (squaredr + squaredi <= 4.0f && i < 2048){                  \n" \
"           zi = (zr + zi) * (zr + zi) - squaredr - squaredi + coord_im;  \n" \
"           zr = squaredr - squaredi + coord_re;                        \n" \
"           squaredr = zr * zr;                                         \n" \
"           squaredi = zi * zi;                                         \n" \
"           ++i;                                                        \n" \
"       }                                                               \n" \
"       output[k] = i % 4;                                              \n" \
"   }                                                                   \n" \
"}                                                                      \n" \
"\n";


static t_image get_display_buffer(void *mlx, uint32_t width, uint32_t height)
{
     t_image display;

     display.width = width;
     display.height = height;
     display.ptr = mlx_new_image(mlx, width, height);
     display.data = (int8_t *)mlx_get_data_addr(display.ptr,
				      &display.bpp,
				      &display.size_line,
				      &display.endian);
     display.size_in_bytes = width * height;
     display.center.x = width / 2;
     display.center.y = height / 2;
     display.aspect_ratio = (float)width / (float)height;
     return (display);
}

void create_cl_device(t_cl_device *cl)
{
     int err;

     if (clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU,
			1, &cl->device_id, NULL) != CL_SUCCESS)
	  exit(1);
     cl->context = clCreateContext(0, 1, &cl->device_id, NULL, NULL, &err);
     if (!cl->context)
	  exit(1);
     cl->commands = clCreateCommandQueue(cl->context, cl->device_id, 0, &err);
     if (!cl->commands)
	  exit(1);
     cl->program = clCreateProgramWithSource(cl->context, 1,
			    (const char **)&julia_source, NULL, &err);
     if (!cl->program)
	  exit(1);
     if (clBuildProgram(cl->program, 0, NULL, NULL, NULL, NULL) != CL_SUCCESS)
	  exit(1);
     cl->kernel = clCreateKernel(cl->program, "julia_kernel", &err);
     if (!cl->kernel || err != CL_SUCCESS)
	  exit(1);
     cl->output = clCreateBuffer(cl->context, CL_MEM_WRITE_ONLY,
				 sizeof(int) * DATA_SIZE, NULL, NULL);
     if (!cl->output)
	  exit(1);
     if (clGetKernelWorkGroupInfo(cl->kernel, cl->device_id,
				    CL_KERNEL_WORK_GROUP_SIZE,
				  sizeof(cl->local), &cl->local, NULL) != CL_SUCCESS)
	  exit(1);
}

void release_cl_device(t_cl_device *cl)
{
     clReleaseMemObject(cl->output);
     clReleaseProgram(cl->program);
     clReleaseKernel(cl->kernel);
     clReleaseCommandQueue(cl->commands);
     clReleaseContext(cl->context);
}


static void setup_window(t_window *win)
{
     win->mlx = mlx_init();
     win->win = mlx_new_window(win->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
     win->disp = get_display_buffer(win->mlx, WIN_WIDTH, WIN_HEIGHT);
     win->splash = get_splash(win->mlx);
     win->time = 0.0;
     win->center.x = (WIN_WIDTH / 2);
     win->center.y = (WIN_HEIGHT / 2);
     win->keys = 0;
     win->initialized = 0;
     win->mods = (t_mods){10.0, -0.7, 0.27015, 0, 0, 0};
     if (win->opts & OPT_GPU)
	  create_cl_device(&win->cl);
}

static void print_welcome_msg(char *program_name)
{
     ft_putstr(program_name);
     ft_putendl(": A 42 Graphics Project - by nmayfiel");
     ft_putendl("Controls:");
     ft_putendl("UP/DWN:\tScale");
     ft_putendl("ESC:\tQuit");
}

/*
** 4 is zoom in, 5 is zoom out, for now
*/
int mouse_hook(int button, int x, int y, t_window *win)
{
     if (button == 4)
     {
	  win->mods.scale /= 1.1;
	  win->mods.xoffset = x - (float)win->disp.center.x;
	  win->mods.yoffset = y - (float)win->disp.center.y;
     }
     else if (button == 5)
     {
	  win->mods.scale *= 1.1;
	  win->mods.xoffset = x - (float)win->disp.center.x;
	  win->mods.yoffset = y - (float)win->disp.center.y;
     }
     win->mods.update = 1;
     return (0);
}

int32_t mouse_moved(int x, int y, t_window *win)
{
     win->mods.xmouse = (x - (float)win->disp.center.x) / win->disp.width;
     win->mods.ymouse = (y - (float)win->disp.center.y) / win->disp.height;
     win->mods.update = 1;
     return (0);
}

char *usage_msg(void)
{
     return ("Usage: ./fractol <type> [options]\n" \
	     "\ttype:\n" \
	     "\t\tjulia\n"			\
             "\t\tmandelbrot\n" \
	     "\t\tship\n" \
	     "\toptions:\n" \
             "\t\t-g, --gpu, use opencl implementation");
}

static void exit_error(int32_t error_code)
{
     if (error_code == E_USAGE)
	  ft_putendl(usage_msg());
     /*else if (error_code == E_BADFILE)
	  perror(NULL);
     else if (error_code == E_BADFORM)
	  ft_putendl_fd(EMSG_BADFORM, 2);
     else if (error_code == E_MALLOC)
     perror(NULL);*/
     exit(0);
}

void parse_options(int argc, char **argv, t_window *win)
{
     int i;

     win->opts = 0;
     if (ft_strequ(argv[0], "julia"))
	  win->opts |= OPT_JULIA;
     else if (ft_strequ(argv[0], "mandelbrot"))
	  win->opts |= OPT_MANDELBROT;
     else if (ft_strequ(argv[0], "ship"))
	  win->opts |= OPT_SHIP;
     else
	  exit_error(E_USAGE);
     i = 1;
     while (i < argc)
     {
	  if (ft_strequ(argv[i], "-g") || ft_strequ(argv[i], "--gpu"))
	       win->opts |= OPT_GPU;
	  else
	       exit_error(E_USAGE);
	  ++i;
     }
}

/*
** Rather than using key hook and mouse hook functions, I chose to use
** the generic mlx_hook function for assigning all event hooks
** You can find the values for event keys in minilibx/mlx_new_window.m
** int mlx_hook(void *win_ptr, int event, int mask, int (*f)(), void *param);
*/

int main(int argc, char **argv)
{
     t_window win;

     if (argc == 1)
	  exit_error(E_USAGE);
     parse_options(argc - 1, argv + 1, &win);
     setup_window(&win);
     win.initialized = 1;
     print_welcome_msg(argv[0]);
     mlx_hook(win.win, 2, 0, remove_key, &win.keys);
     mlx_hook(win.win, 4, 0, mouse_hook, &win);
     mlx_hook(win.win, 6, 0, mouse_moved, &win);
     mlx_hook(win.win, 3, 0, add_key, &win.keys);
     mlx_hook(win.win, 17, 0, close_hook, &win);
     mlx_loop_hook(win.mlx, main_loop, &win);
     mlx_loop(win.mlx);
     return (0);
}
