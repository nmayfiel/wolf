/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 14:43:18 by nmayfiel          #+#    #+#             */
/*   Updated: 2016/11/23 22:02:42 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *big, const char *little)
{
	int		i;

	if (*little == '\0')
		return ((char *)big);
	while (*big != '\0')
	{
		i = 0;
		while (big[i] == little[i] && big[i] != '\0')
			i++;
		if (little[i] == '\0')
			return ((char *)big);
		big++;
	}
	return (NULL);
}
