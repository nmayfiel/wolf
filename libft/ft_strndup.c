/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 18:13:15 by nmayfiel          #+#    #+#             */
/*   Updated: 2016/12/09 20:25:39 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (n + 1));
	if (dest)
		while (s1[i] != '\0' && (size_t)i < n)
		{
			dest[i] = s1[i];
			i++;
		}
	else
		return (NULL);
	dest[i] = '\0';
	return (dest);
}
