/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 08:44:49 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/06/30 02:37:31 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "wolf.h"
#include <mlx.h>
#include <math.h>

void	clear_image(t_image *img, int32_t color)
{
	int32_t i;
	int32_t *buffer;

	buffer = (int32_t *)img->data;
	i = 0;
	while (i < img->size_in_pixels)
	{
		buffer[i] = color;
		++i;
	}
}

void draw_rectangle(t_image *img, t_rect rect)
{
     int32_t *buffer;
     int32_t row;
     int32_t col;
     int32_t pos;

     buffer = (int32_t *)img->data;
     row = rect.y;
     while (row < rect.y + rect.height)
     {
	  col = rect.x;
	  while (col < rect.x + rect.width)
	  {
	       pos = col + (img->width * row);
	       if (pos >= 0
		   && pos < img->size_in_pixels
		   && col >= 0
		   && col < img->width
		   && row >= 0
		   && row < img->height)
		    buffer[col + (img->width * row)] = rect.color;
	       ++col;
	  }
	  ++row;
     }
}
