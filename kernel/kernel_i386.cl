/*
** 32 Bit OpenCL Kernel
*/

typedef struct s_mods
{
     float scale;
     float xmouse;
     float ymouse;
     float xoffset;
     float yoffset;
     int iterations;
     int update;
} t_mods;

typedef struct s_winfo
{
     int width;
     int height;
     int centerx;
     int centery;
     float aspect;
} t_winfo;

__kernel void burning_ship_kernel(
     __global int *output,
     const unsigned int count,
     int width,
     int height,
     float scale,
     float aspect)
{
     int k = get_global_id(0);
     if(k < count){
	  int x = k % width;
	  int y = height - (k / width);
	  float coord_re = (x - width / 2.0f) * (scale / width * aspect);
	  float coord_im = (y - height / 2.0f) * (scale / height);
	  float zr = coord_re;
	  float zi = coord_im;
	  float squaredr = zr * zr;
	  float squaredi = zi * zi;
	  int i = 0;
	  while (squaredr + squaredi <= 4.0f && i < 2048){
	       zi = zr * zi;
	       if(zi < 0)
		    zi = -zi;
	       zi = zi + zi - coord_im;
	       zr = squaredr - squaredi + coord_re;
	       squaredr = zr * zr;
	       squaredi = zi * zi;
	       ++i;
	  }
	  output[k] = i % 4;
     }
}

__kernel void julia_kernel(
     __global int *output,
     const unsigned int count,
     int width,
     int height,
     double scale,
     double aspect,
     double mousex,
     double mousey)
{
     int k = get_global_id(0);
     if(k < count){
	  int x = k % width;
	  int y = height - (k / width);
	  double coord_im = mousex * 2.0f;
	  double coord_re = mousey * 2.0f;
	  double zr = (x - width / 2.0f) * (scale / width * aspect);
	  double zi = (y - height / 2.0f) * (scale / height);
	  double squaredr = zr * zr;
	  double squaredi = zi * zi;
	  int i = 0;
	  while (squaredr + squaredi <= 4.0f && i < 4096){
	       zi = (zr + zi) * (zr + zi) - squaredr - squaredi + coord_im;
	       zr = squaredr - squaredi + coord_re;
	       squaredr = zr * zr;
	       squaredi = zi * zi;
	       ++i;
	  }
	  output[k] = i % 4;
     }
}

__kernel void mandelbrot_kernel(
     __global int *output,
     const unsigned int count,
     int width,
     int height,
     float scale,
     float aspect)
{
     int k = get_global_id(0);
     if(k < count){
	  int x = k % width;
	  int y = height - (k / width);
	  float coord_re = (x - width / 2.0f) * (scale / width * aspect);
	  float coord_im = (y - height / 2.0f) * (scale / height);
	  float zr = 0;
	  float zi = 0;
	  float squaredr = zr * zr;
	  float squaredi = zi * zi;
	  int i = 0;
	  while (squaredr + squaredi <= 4.0f && i < 2048){
	       zi = (zr + zi) * (zr + zi) - squaredr - squaredi + coord_im;
	       zr = squaredr - squaredi + coord_re;
	       squaredr = zr * zr;
	       squaredi = zi * zi;
	       ++i;
	  }
	  output[k] = i % 4;
     }
}
