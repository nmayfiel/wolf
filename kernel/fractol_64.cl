/*
** 64 Bit OpenCL Kernel
*/

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
	  double coord_im = mousex * 2.0f;
	  double coord_re = mousey * 2.0f;
	  double zr = offsetx + (x - width / 2.0f) * scale;
	  double zi = offsety + (y - height / 2.0f) * scale;
	  double squaredr = zr * zr;
	  double squaredi = zi * zi;
	  int i = 0;
	  while (squaredr + squaredi <= 4.0f && i < iterations){
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
	  double coord_re = offsetx + (x - width / 2.0f) * scale;
	  double coord_im = offsety + (y - height / 2.0f) * scale;
	  double zr = 0;
	  double zi = 0;
	  double squaredr = zr * zr;
	  double squaredi = zi * zi;
	  int i = 0;
	  while (squaredr + squaredi <= 4.0f && i < iterations){
	       zi = (zr + zi) * (zr + zi) - squaredr - squaredi + coord_im;
	       zr = squaredr - squaredi + coord_re;
	       squaredr = zr * zr;
	       squaredi = zi * zi;
	       ++i;
	  }
	  output[k] = i % num_colors;
     }
}
