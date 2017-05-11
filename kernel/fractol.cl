/*
** 32 Bit OpenCL Kernel
*/

__kernel void burning_ship_kernel(
     __global int *output,
     const unsigned int count,
     int width,
     int height,
     float scale,
     float mousex,
     float mousey,
     float offsetx,
     float offsety,
     int iterations, int num_colors)
{
     int k = get_global_id(0);
     if(k < count){
	  int x = k % width;
	  int y = height - (k / width);
	  float coord_re = offsetx + (x - width / 2.0) * scale;
	  float coord_im = offsety + (y - height / 2.0) * scale;
	  float zr = coord_re;
	  float zi = coord_im;
	  float squaredr = zr * zr;
	  float squaredi = zi * zi;
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
     float scale,
     float mousex,
     float mousey,
     float offsetx,
     float offsety,
     int iterations, int num_colors)
{
     int k = get_global_id(0);
     if(k < count){
	  int x = k % width;
	  int y = height - (k / width);
	  float coord_im = mousex * 2.0f;
	  float coord_re = mousey * 2.0f;
	  float zr = offsetx + (x - width / 2.0f) * scale;
	  float zi = offsety + (y - height / 2.0f) * scale;
	  float squaredr = zr * zr;
	  float squaredi = zi * zi;
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
     float scale,
     float mousex,
     float mousey,
     float offsetx,
     float offsety,
     int iterations, int num_colors)
{
     int k = get_global_id(0);
     if(k < count){
	  int x = k % width;
	  int y = height - (k / width);
	  float coord_re = offsetx + (x - width / 2.0f) * scale;
	  float coord_im = offsety + (y - height / 2.0f) * scale;
	  float zr = 0;
	  float zi = 0;
	  float squaredr = zr * zr;
	  float squaredi = zi * zi;
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
