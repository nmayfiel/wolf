/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 17:12:30 by nmayfiel          #+#    #+#             */
/*   Updated: 2016/12/09 15:20:34 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	len = ft_strlen(dst);
	i = len;
	j = 0;
	while (src[j] != '\0' && (size_t)i < size - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (size == 0)
	{
		return (len);
		dst[0] = '\0';
	}
	dst[i] = '\0';
	if ((size_t)i > size - 1)
		return (size + ft_strlen(src));
	return (len + ft_strlen(src));
}
