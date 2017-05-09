/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_x86_64.cl                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 22:53:53 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/05/09 03:07:44 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** x86_64
** 64 Bit OpenCL Kernel
*/

#pragma OPENCL EXTENSION cl_khr_fp64 : enable

__kernel void burning_ship_kernel(
     __global int *output,
     const unsigned int count,
     int width,
     int height,
     double scale,
     double mousex,
     double mousey,
     double offsetx,
     double offsety,
     int iterations, int num_colors)
{
     int k = get_global_id(0);
     if(k < count){
	  int x = k % width;
	  int y = height - (k / width);
	  double coord_re = offsetx + (x - width / 2.0) * scale;
	  double coord_im = offsety + (y - height / 2.0) * scale;
	  double zr = coord_re;
	  double zi = coord_im;
	  double squaredr = zr * zr;
	  double squaredi = zi * zi;
	  int i = 0;
	  while (squaredr + squaredi <= 4.0 && i < iterations){
	       zi = zr * zi;
	       if(zi < 0)
		    zi = -zi;
	       zi = zi + zi - coord_im;
	       zr = squaredr - squaredi + coord_re;
	       squaredr = zr * zr;
	       squaredi = zi * zi;
	       ++i;
	  }
	  output[k] = i % num_colors;
     }
}

__kernel void julia_kernel(
     __global int *output,
     const unsigned int count,
     int width,
     int height,
     double scale,
     double mousex,
     double mousey,
     double offsetx,
     double offsety,
     int iterations, int num_colors)
{
     int k = get_global_id(0);
     if(k < count){
	  int x = k % width;
	  int y = height - (k / width);
	  double coord_im = mousex * 2.0;
	  double coord_re = mousey * 2.0;
	  double zr = offsetx + (x - width / 2.0) * scale;
	  double zi = offsety + (y - height / 2.0) * scale;
	  double squaredr = zr * zr;
	  double squaredi = zi * zi;
	  int i = 0;
	  while (squaredr + squaredi <= 4.0 && i < iterations){
	       zi = (zr + zi) * (zr + zi) - squaredr - squaredi + coord_im;
	       zr = squaredr - squaredi + coord_re;
	       squaredr = zr * zr;
	       squaredi = zi * zi;
	       ++i;
	  }
	  output[k] = i % num_colors;
     }
}

__kernel void mandelbrot_kernel(
     __global int *output,
     const unsigned int count,
     int width,
     int height,
     double scale,
     double mousex,
     double mousey,
     double offsetx,
     double offsety,
     int iterations, int num_colors)
{
     int k = get_global_id(0);
     if(k < count){
	  int x = k % width;
	  int y = height - (k / width);
	  double coord_re = offsetx + (x - width / 2.0) * scale;
	  double coord_im = offsety + (y - height / 2.0) * scale;
	  double zr = 0;
	  double zi = 0;
	  double squaredr = zr * zr;
	  double squaredi = zi * zi;
	  int i = 0;
	  while (squaredr + squaredi <= 4.0 && i < iterations){
	       zi = (zr + zi) * (zr + zi) - squaredr - squaredi + coord_im;
	       zr = squaredr - squaredi + coord_re;
	       squaredr = zr * zr;
	       squaredi = zi * zi;
	       ++i;
	  }
	  output[k] = i % num_colors;
     }
}
