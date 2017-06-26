/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mallocat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 14:44:24 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/01/13 14:44:25 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_mallocat(char *dst, const char *src)
{
	size_t	len;
	size_t	new_len;

	if (!src)
		return (NULL);
	if (!dst)
		return (ft_strdup(src));
	len = ft_strlen(dst) + 1;
	new_len = ft_strlen(dst) + ft_strlen(src) + 1;
	dst = ft_realloc(dst, len, new_len);
	if (!dst)
		return (NULL);
	ft_strcat(dst, src);
	return (dst);
}
