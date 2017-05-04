////////////////////////////////////////////////////////////////////////////////
 
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <OpenCL/opencl.h>
 
////////////////////////////////////////////////////////////////////////////////
 
// Use a static data size for simplicity
//
#define DATA_SIZE (768 * 512)
 
////////////////////////////////////////////////////////////////////////////////
 
// Simple compute kernel which computes the square of an input array 
//
const char *burning_ship_source = "\n" \
"__kernel void burning_ship_kernel(                                     \n" \
"   __global int *output,                                               \n" \
"   const unsigned int count,                                           \n" \
"   const int width,                                                    \n" \
"   const int height,                                                   \n" \
"   const float scale,                                                  \n" \
"   const float aspect)                                                 \n" \
"{                                                                      \n" \
"   int k = get_global_id(0);                                           \n" \
"   if(k < count){                                                      \n" \
"       int x = k % width;                                              \n" \
"       int y = k / width;                                              \n" \
"       float coord_re = (x - width / 2.0) * (scale / width * aspect);  \n" \
"       float coord_im = (y - height / 2.0) * (scale / height);         \n" \
"       float zx = coord_re;                                            \n" \
"       float zy = coord_im;                                            \n" \
"       float squaredx = zx * zx;                                       \n" \
"       float squaredy = zy * zy;                                       \n" \
"       int i = 0;                                                      \n" \
"       unsigned char r = 0;                                            \n" \
"       unsigned char g = 255;                                          \n" \
"       while (squaredx + squaredy <= 4.0f && i < 2048){                \n" \
"           zy = zx * zy;                                               \n" \
"           if(zy < 0.0f)                                               \n" \
"               zy = -zy;                                               \n" \
"           zy = zy + zy - coord_im;                                    \n" \
"           zx = squaredx - squaredy + coord_re;                        \n" \
"           squaredx = zx * zx;                                         \n" \
"           squaredy = zy * zy;                                         \n" \
"           g -= 16;                                                    \n" \
"           r += 16;                                                    \n" \
"           ++i;                                                        \n" \
"       }                                                               \n" \
"       output[k] = (int)(255 | g << 8 | r << 16);                      \n" \
"   }                                                                   \n" \
"}                                                                      \n" \
"\n";
 
////////////////////////////////////////////////////////////////////////////////

typedef struct s_cl_device
{
     cl_device_id device_id;
     cl_context context;
     cl_command_queue commands;
     cl_program program;
     cl_kernel kernel;
     cl_mem output; // device memory used for the output array
     size_t local;
} t_cl_device;

/*
** TODO: setup_cl_device needs more robust errors like those from
** your fdf project...
** NOTE: Potential bug, getkernelworkgroupinfo was originally set
** after the arguments were added in main, make sure that this is
** okay.
*/

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
			    (const char **)&burning_ship_source, NULL, &err);
     if (!cl->program)
	  exit(1);
     if (clBuildProgram(cl->program, 0, NULL, NULL, NULL, NULL) != CL_SUCCESS)
	  exit(1);
     cl->kernel = clCreateKernel(cl->program, "burning_ship_kernel", &err);
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

void release_device(t_cl_device *cl)
{
     clReleaseMemObject(cl->output);
     clReleaseProgram(cl->program);
     clReleaseKernel(cl->kernel);
     clReleaseCommandQueue(cl->commands);
     clReleaseContext(cl->context);
}

int main(int argc, char** argv)
{
    int err;                            // error code returned from api calls
      
    int results[DATA_SIZE];           // results returned from device
 
    size_t global;                      // global domain size for our calculation

    t_cl_device cl;
    create_cl_device(&cl);
    
    unsigned int count = DATA_SIZE;


////////////////////////////////////////////////////////////////////////////////////
// MUST BE PERFORMED EACH TIME THE KERNEL IS RUN
////////////////////////////////////////////////////////////////////////////////////


    // Get the maximum work group size for executing the kernel on the device
    //

    for (int m = 0; m < 5000; m++)
    {
    // Set the arguments to our compute kernel
    //
    float scale = 1.0;
    float aspect = 768 / 512;
    int width = 768;
    int height = 512;

    err = 0;
    err |= clSetKernelArg(cl.kernel, 0, sizeof(cl_mem), &cl.output);
    err |= clSetKernelArg(cl.kernel, 1, sizeof(unsigned int), &count);
    err |= clSetKernelArg(cl.kernel, 2, sizeof(int), &height);
    err |= clSetKernelArg(cl.kernel, 3, sizeof(int), &width);
    err |= clSetKernelArg(cl.kernel, 4, sizeof(float), &scale);
    err |= clSetKernelArg(cl.kernel, 5, sizeof(float), &aspect);
    
    if (err != CL_SUCCESS)
    {
        printf("Error: Failed to set kernel arguments! %d\n", err);
        exit(1);
    }
 
    // Execute the kernel over the entire range of our 1d input data set
    // using the maximum number of work group items for this device
    //
    global = count;
    err = clEnqueueNDRangeKernel(cl.commands, cl.kernel, 1, NULL, &global, &cl.local, 0, NULL, NULL);
    if (err)
    {
        printf("Error: Failed to execute kernel!\n");
        return EXIT_FAILURE;
    }
 
    // Wait for the command commands to get serviced before reading back results
    //
    clFinish(cl.commands);
 
    // Read back the results from the device to verify the output
    //
    err = clEnqueueReadBuffer(cl.commands, cl.output, CL_TRUE, 0, sizeof(int) * count, results, 0, NULL, NULL );  
    if (err != CL_SUCCESS)
    {
        printf("Error: Failed to read output array! %d\n", err);
        exit(1);
    }
    
    printf("%d  /////////////////////////////////////////////////////////////\n", m);
    }
    
    // Shutdown and cleanup
    //
    release_device(&cl);
 
    return 0;
}
