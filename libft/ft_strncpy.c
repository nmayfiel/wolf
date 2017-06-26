/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:14:03 by nmayfiel          #+#    #+#             */
/*   Updated: 2016/11/23 15:36:43 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	int i;

	i = 0;
	while ((size_t)i < len && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	while ((size_t)i < len)
		dst[i++] = '\0';
	return (dst);
}
