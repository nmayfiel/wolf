/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 17:42:01 by nmayfiel          #+#    #+#             */
/*   Updated: 2016/11/23 16:57:51 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			s += i;
			i = 0;
		}
		i++;
	}
	if (c == '\0')
		s += i;
	if (*s == c)
		return ((char *)s);
	else
		return (NULL);
}
