/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 14:46:07 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/01/13 14:46:08 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

void		*ft_realloc(void *ptr, size_t size, size_t new_size)
{
	unsigned char	*ret;

	ret = (unsigned char *)malloc(sizeof(unsigned char) * new_size);
	if (!ret)
		return (NULL);
	if (size <= new_size)
		ft_memcpy(ret, ptr, size);
	else if (size > new_size)
		ft_memcpy(ret, ptr, new_size);
	free(ptr);
	return (ret);
}
