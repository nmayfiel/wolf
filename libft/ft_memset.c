/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:12:59 by nmayfiel          #+#    #+#             */
/*   Updated: 2016/11/18 19:06:25 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *ret;

	ret = (unsigned char *)b;
	while (len--)
	{
		*(unsigned char *)b = (unsigned char)c;
		b++;
	}
	return (ret);
}
