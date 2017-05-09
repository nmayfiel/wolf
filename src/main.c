/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 17:23:55 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/05/09 03:11:47 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/opencl.h>
#include "fractal.h"
#include <libft.h>
#include <mlx.h>
#include <stdlib.h>

#include <stdio.h>

// TODO: add iterations to mods, increase/decrease with keys
// TODO: rework the OpenCL kernel for 32 bit and 64 bit GPUs
// TODO: add xoffset and yoffset parameters to the kernel
// TODO: compile the kernel offline

const char *kernel_source = "\n" \
"__kernel void burning_ship_kernel(\n" \
"     __global int *output,\n" \
"     const unsigned int count,\n" \
"     int width,\n" \
"     int height,\n" \
"     double scale,\n" \
"     double mousex,\n" \
"     double mousey,\n" \
"     double offsetx,\n" \
"     double offsety,\n" \
"     int iterations, int num_colors)\n" \
"{\n" \
"     int k = get_global_id(0);\n" \
"     if(k < count){\n" \
"	  int x = k % width;\n" \
"	  int y = height - (k / width);\n" \
"	  double coord_re = offsetx + (x - width / 2.0) * scale;\n" \
"	  double coord_im = offsety + (y - height / 2.0) * scale;\n" \
"	  double zr = coord_re;\n" \
"	  double zi = coord_im;\n" \
"	  double squaredr = zr * zr;\n" \
"	  double squaredi = zi * zi;\n" \
"	  int i = 0;\n" \
"	  while (squaredr + squaredi <= 4.0 && i < iterations){\n" \
"	       zi = zr * zi;\n" \
"	       if(zi < 0)\n" \
"		    zi = -zi;\n" \
"	       zi = zi + zi - coord_im;\n" \
"	       zr = squaredr - squaredi + coord_re;\n" \
"	       squaredr = zr * zr;\n" \
"	       squaredi = zi * zi;\n" \
"	       ++i;\n" \
"	  }\n" \
"	  output[k] = i % num_colors;\n" \
"     }\n" \
"}\n" \
"\n" \
"__kernel void julia_kernel(\n" \
"     __global int *output,\n" \
"     const unsigned int count,\n" \
"     int width,\n" \
"     int height,\n" \
"     double scale,\n" \
"     double mousex,\n" \
"     double mousey,\n" \
"     double offsetx,\n" \
"     double offsety,\n" \
"     int iterations, int num_colors)\n" \
"{\n" \
"     int k = get_global_id(0);\n" \
"     if(k < count){\n" \
"	  int x = k % width;\n" \
"	  int y = height - (k / width);\n" \
"	  double coord_im = mousex * 2.0f;\n" \
"	  double coord_re = mousey * 2.0f;\n" \
"	  double zr = offsetx + (x - width / 2.0f) * scale;\n" \
"	  double zi = offsety + (y - height / 2.0f) * scale;\n" \
"	  double squaredr = zr * zr;\n" \
"	  double squaredi = zi * zi;\n" \
"	  int i = 0;\n" \
"	  while (squaredr + squaredi <= 4.0f && i < iterations){\n" \
"	       zi = (zr + zi) * (zr + zi) - squaredr - squaredi + coord_im;\n" \
"	       zr = squaredr - squaredi + coord_re;\n" \
"	       squaredr = zr * zr;\n" \
"	       squaredi = zi * zi;\n" \
"	       ++i;\n" \
"	  }\n" \
"	  output[k] = i % num_colors;\n" \
"     }\n" \
"}\n" \
"\n" \
"__kernel void mandelbrot_kernel(\n" \
"     __global int *output,\n" \
"     const unsigned int count,\n" \
"     int width,\n" \
"     int height,\n" \
"     double scale,\n" \
"     double mousex,\n" \
"     double mousey,\n" \
"     double offsetx,\n" \
"     double offsety,\n" \
"     int iterations, int num_colors)\n" \
"{\n" \
"     int k = get_global_id(0);\n" \
"     if(k < count){\n" \
"	  int x = k % width;\n" \
"	  int y = height - (k / width);\n" \
"	  double coord_re = offsetx + (x - width / 2.0f) * scale;\n" \
"	  double coord_im = offsety + (y - height / 2.0f) * scale;\n" \
"	  double zr = 0;\n" \
"	  double zi = 0;\n" \
"	  double squaredr = zr * zr;\n" \
"	  double squaredi = zi * zi;\n" \
"	  int i = 0;\n" \
"	  while (squaredr + squaredi <= 4.0f && i < iterations){\n" \
"	       zi = (zr + zi) * (zr + zi) - squaredr - squaredi + coord_im;\n" \
"	       zr = squaredr - squaredi + coord_re;\n" \
"	       squaredr = zr * zr;\n" \
"	       squaredi = zi * zi;\n" \
"	       ++i;\n" \
"	  }\n" \
"	  output[k] = i % num_colors;\n" \
"     }\n" \
     "}\n\n";

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

static void check_status(char* msg, cl_int err) {
     if (err != CL_SUCCESS) {
	  fprintf(stderr, "%s failed. Error: %d\n", msg, err);
     }
     
}

void create_cl_device(t_cl_device *cl, int32_t win_opts)
{
     int err;

     if (clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU,
			1, &cl->device_id, NULL) != CL_SUCCESS)
	  exit(1);
     cl->context = clCreateContext(NULL, 1, &cl->device_id, NULL, NULL, &err);
     check_status("clCreateContext", err);
     cl->commands = clCreateCommandQueue(cl->context, cl->device_id, 0, &err);
     check_status("clCreateCommandQueue", err);

     const char *bitcode_path = "kernel/kernel.bc";
     size_t len = ft_strlen(bitcode_path);
     
     cl->program = clCreateProgramWithBinary(cl->context, 1, &cl->device_id, &len,
				 (const unsigned char**)&bitcode_path, NULL, &err);
     check_status("clCreateProgramWithBinary", err);

//     cl->program = clCreateProgramWithSource(cl->context, 1,
//			    (const char **)&kernel_source, NULL, &err);
     if (!cl->program)
     {
	  printf("Program is no good\n");
	  exit(1);
     }
     err = clBuildProgram(cl->program, 1, &cl->device_id, NULL, NULL, NULL);
     check_status("clBuildProgram", err);

if (err == CL_BUILD_PROGRAM_FAILURE) {
	  // Determine the size of the log
	  size_t log_size;
	  clGetProgramBuildInfo(cl->program, cl->device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

	  // Allocate memory for the log
	  char *log = (char *) malloc(log_size);

	  // Get the log
	  clGetProgramBuildInfo(cl->program, cl->device_id, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);

	  // Print the log
	  printf("%s\n", log);
     }

     if (win_opts & OPT_JULIA)
	  cl->kernel = clCreateKernel(cl->program, "julia_kernel", &err);
     else if (win_opts & OPT_MANDELBROT)
	  cl->kernel = clCreateKernel(cl->program, "mandelbrot_kernel", &err);
     else if (win_opts & OPT_SHIP)
	  cl->kernel = clCreateKernel(cl->program, "burning_ship_kernel", &err);
     if (!cl->kernel || err != CL_SUCCESS)
	  exit(1);
     cl->output = clCreateBuffer(cl->context, CL_MEM_WRITE_ONLY,
				 sizeof(int) * DATA_SIZE, NULL, NULL);
     if (!cl->output)
     {
	  printf("clCreateBuffer Failed\n");
	  exit(1);
     }
     if (clGetKernelWorkGroupInfo(cl->kernel, cl->device_id,
				    CL_KERNEL_WORK_GROUP_SIZE,
				  sizeof(cl->local), &cl->local, NULL) != CL_SUCCESS)
     {
	  printf("clGetKernelWorkGroupInfo Failed\n");
	  exit(1);
     }
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
     win->mods = (t_mods){0.02, -0.7, 0.27015, 0, 0, 0};
     if (win->opts & OPT_GPU)
	  create_cl_device(&win->cl, win->opts);
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
	 
	  win->mods.xoffset -= win->mods.scale * ((double)x - (float)win->disp.center.x) / 11;
	  win->mods.yoffset += win->mods.scale * ((double)y - (float)win->disp.center.y) / 11;
	  win->mods.scale *= 1.1;
     }
     else if (button == 5)
     {
	  win->mods.xoffset += win->mods.scale * ((double)x - (double)win->disp.center.x) / 11;
	  win->mods.yoffset -= win->mods.scale * ((double)y - (double)win->disp.center.y) / 11;
	  win->mods.scale /=  1.1;
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

void print_usage(char *name)
{
     ft_putstr("Usage:\t");
     ft_putstr(name);
     ft_putstr(" julia|mandelbrot|ship [-o opencl]\n");
     exit(0);
}


// TODO: Remove E_USAGE and EMSG_USAGE macros

static void exit_error(int32_t error_code)
{
     (void)error_code;
     /*else if (error_code == E_BADFILE)
	  perror(NULL);
     else if (error_code == E_BADFORM)
	  ft_putendl_fd(EMSG_BADFORM, 2);
     else if (error_code == E_MALLOC)
     perror(NULL);*/
     exit(0);
}

int parse_options(int argc, char **argv, t_window *win)
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
	  return (-1);
     i = 1;
     while (i < argc)
     {
	  if (ft_strequ(argv[i], "-o"))
	       win->opts |= OPT_GPU;
	  else
	       return (-1);
	  ++i;
     }
     return (1);
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
	  print_usage(argv[0]);
     if (parse_options(argc - 1, argv + 1, &win) == -1)
	  print_usage(argv[0]);
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
     if (0)
	  exit_error(E_USAGE);
     return (0);
}
