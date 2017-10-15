#include "wolf.h"

float		clamp_degrees_f(float angle)
{
	float new_angle;

	new_angle = angle;
	if (new_angle >= 180)
		new_angle = -180.0 + (new_angle - 180.0);
	if (new_angle < -180.0)
		new_angle = 180.0 + (new_angle + 180.0);
	return (new_angle);
}

size_t str_array_size(char **arr)
{
     size_t i;

     i = 0;
     while (arr[i] != NULL)
	  ++i;
     return (i);
}
