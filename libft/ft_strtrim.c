/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 13:34:16 by nmayfiel          #+#    #+#             */
/*   Updated: 2016/12/09 14:22:05 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strtrim(char const *s)
{
	char		*trim;
	size_t		len;
	int			i;

	if (!s)
		return (NULL);
	while (*s == 011 || *s == 012 || *s == 040)
		s++;
	len = ft_strlen(s);
	while (len > 0 &&
			(s[len - 1] == 011 || s[len - 1] == 012 || s[len - 1] == 040))
		len--;
	trim = ft_strnew(len);
	if (!trim)
		return (NULL);
	i = 0;
	while ((size_t)i < len)
	{
		trim[i] = s[i];
		i++;
	}
	trim[i] = '\0';
	return (trim);
}
