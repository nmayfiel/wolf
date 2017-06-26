/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 16:14:03 by nmayfiel          #+#    #+#             */
/*   Updated: 2016/12/09 20:29:48 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*srcp;
	unsigned char	*dstp;
	size_t			diff;

	srcp = (unsigned char *)src;
	dstp = (unsigned char *)dst;
	diff = dstp - srcp;
	if (diff >= len)
		dst = ft_memcpy(dstp, srcp, len);
	else
		dst = ft_memcpyr(dstp, srcp, len);
	return (dst);
}
