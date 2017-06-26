/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpyr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 17:55:50 by nmayfiel          #+#    #+#             */
/*   Updated: 2016/11/23 15:14:46 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpyr(void *dst, const void *src, size_t n)
{
	void	*ret;
	int		i;

	ret = dst;
	i = 1;
	while ((size_t)i < n)
	{
		src++;
		dst++;
		i++;
	}
	while (i > 0)
	{
		*(unsigned char *)dst = *(unsigned char *)src;
		dst--;
		src--;
		i--;
	}
	return (ret);
}
