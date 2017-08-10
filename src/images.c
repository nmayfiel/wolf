/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 00:23:10 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/08/10 00:31:44 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <mlx.h>
#include <stdlib.h>

t_image		get_image_of_size(void *mlx, uint32_t width, uint32_t height)
{
	t_image image;

	image.width = width;
	image.height = height;
	image.ptr = mlx_new_image(mlx, width, height);
	image.data = (int8_t *)mlx_get_data_addr(image.ptr,
			&image.bpp,
			&image.size_line,
			&image.endian);
	image.size_in_pixels = width * height;
	image.size_in_bytes = image.size_line * height;
	image.center.x = width / 2;
	image.center.y = height / 2;
	return (image);
}

t_image		get_texture(void *mlx, char *fn)
{
	t_image	image;

	image.ptr = png_file_to_image(mlx, fn, &image.width, &image.height);
	image.data = (int8_t *)mlx_get_data_addr(image.ptr,
			&image.bpp,
			&image.size_line,
			&image.endian);
	image.center.x = image.width / 2;
	image.center.y = image.height / 2;
	image.size_in_pixels = image.width * image.height;
	image.size_in_bytes = image.size_line * image.height;
	return (image);
}

int32_t		**get_vertical_image_buffer_map(t_image *image)
{
	int32_t	*buffer;
	int32_t	**vertical_buffer;
	int		i;
	int		j;
	int		k;

	buffer = (int32_t *)image->data;
	vertical_buffer = (int32_t **)malloc(sizeof(int32_t *)
			* image->size_in_pixels);
	i = 0;
	k = 0;
	while (i < image->width)
	{
		j = 0;
		while (j < image->height)
		{
			vertical_buffer[k] = &buffer[(image->width * j) + i];
			++j;
			++k;
		}
		++i;
	}
	return (vertical_buffer);
}
