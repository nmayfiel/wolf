/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 16:30:54 by nmayfiel          #+#    #+#             */
/*   Updated: 2016/12/05 19:06:46 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		*us;
	unsigned char		cc;

	us = (unsigned char *)s;
	cc = (unsigned char)c;
	while (n-- > 0)
	{
		if (*us == cc)
			return (us);
		us++;
	}
	return (NULL);
}
