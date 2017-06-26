/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 14:51:43 by nmayfiel          #+#    #+#             */
/*   Updated: 2016/11/23 17:06:13 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int	i;
	int	j;

	if (*little == '\0')
		return ((char *)big);
	j = 0;
	while (*big != '\0' && (size_t)j < len)
	{
		i = 0;
		while (big[i] == little[i] && big[i] != '\0' && (size_t)(j + i) < len)
			i++;
		if (little[i] == '\0')
			return ((char *)big);
		j++;
		big++;
	}
	return (NULL);
}
