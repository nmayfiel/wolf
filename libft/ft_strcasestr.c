/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcasestr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:21:18 by nmayfiel          #+#    #+#             */
/*   Updated: 2016/11/14 19:14:41 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strcasestr(const char *big, const char *little)
{
	int	i;

	if (*little == '\0')
		return ((char *)big);
	while (*big != '\0')
	{
		i = 0;
		while (ft_tolower(big[i]) == ft_tolower(little[i]) && big[i] != '\0')
			i++;
		if (little[i] == '\0')
			return ((char *)big);
		big++;
	}
	return (NULL);
}
