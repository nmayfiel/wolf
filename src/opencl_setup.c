#include "fractol.h"


#include <stdio.h>

void		check_err(cl_int err)
{
	if (err != CL_SUCCESS)
	{
		ft_putendl("Error\n");
		exit(0);
	} 
}

/*
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
*/

static char	*kernel_source_from_file(const char *file_path)
{
	int fd;
	char *result;
	char *line;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		// print error, default to cpu
		// // you can do this by passing err into here,
		// // and setting it if something goes wrong,
		// // then go back to default implementation
		// // from there.
	}
	while (get_next_line(fd, &line) == 1)
	{
		if (!result)
			result = ft_strdup(line);
		else
			result = ft_strjoin(result, line);
		free(line);
	}
	close(fd);
	return (result);
}

char		*get_kernel(int32_t *win_opts)
{
	if (*win_opts & OPT_JULIA)
		return (ft_strdup("julia_kernel"));
	else if (*win_opts & OPT_MANDELBROT)
		return (ft_strdup("mandelbrot_kernel"));
	return (ft_strdup("burning_ship_kernel"));
}
/*
get_device_id();
query_device_bits();
get_context();
create_program();
build_program();
create_kernel();
create_buffer();
get_workgroup_info();
*/
void		create_cl_device(t_cl_device *cl, int32_t *win_opts)
{
	cl_int err;
	char *kernel_source;
	cl_uint address_bits;

	err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &cl->device_id, NULL);
	check_err(err);
	cl->context = clCreateContext(NULL, 1, &cl->device_id, NULL, NULL, &err);
	check_err(err);
	cl->commands = clCreateCommandQueue(cl->context, cl->device_id, 0, &err);
	check_err(err);
	err = clGetDeviceInfo(cl->device_id, CL_DEVICE_ADDRESS_BITS, sizeof(address_bits), &address_bits, NULL);
	if (address_bits == 64)
		*win_opts |= OPT_64;
	if (*win_opts & OPT_64)
		kernel_source = kernel_source_from_file("kernel/fractol_64.cl");
	else
		kernel_source = kernel_source_from_file("kernel/fractol.cl");
	cl->program = clCreateProgramWithSource(cl->context, 1, (const char **)&kernel_source, NULL, &err);
	check_err(err);
	err = clBuildProgram(cl->program, 1, &cl->device_id, NULL, NULL, NULL);
	check_err(err);
	cl->kernel = clCreateKernel(cl->program, get_kernel(win_opts), &err);
	check_err(err);
	cl->output = clCreateBuffer(cl->context, CL_MEM_WRITE_ONLY, sizeof(int) * DATA_SIZE, NULL, NULL);
	err = clGetKernelWorkGroupInfo(cl->kernel, cl->device_id, CL_KERNEL_WORK_GROUP_SIZE, sizeof(cl->local), &cl->local, NULL);
	check_err(err);
	free(kernel_source);
}

void		release_cl_device(t_cl_device *cl)
{
	clReleaseMemObject(cl->output);
	clReleaseProgram(cl->program);
	clReleaseKernel(cl->kernel);
	clReleaseCommandQueue(cl->commands);
	clReleaseContext(cl->context);
}
