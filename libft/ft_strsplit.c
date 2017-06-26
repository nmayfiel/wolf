/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 16:25:41 by nmayfiel          #+#    #+#             */
/*   Updated: 2016/12/09 20:25:57 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

static int		ft_num_words(const char *s, char c)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (*s != '\0')
	{
		if (*s != c)
			++i;
		while (*s != c && *(s + 1) != '\0')
			++s;
		++s;
	}
	return (i);
}

char			**ft_strsplit(const char *s, char c)
{
	char	**ret;
	int		len;
	int		i;
	char	c2;

	if (!s)
		return (NULL);
	c2 = c;
	while (*s == c && *s != '\0')
		++s;
	len = ft_num_words(s, c);
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		c2 = ft_strchr(s, c) == NULL ? '\0' : c;
		ret[i] = ft_strndup(s, ft_strchr(s, c2) - s);
		s = ft_strchr(s, c2);
		while (*s == c && *(s + 1) != '\0')
			++s;
	}
	ret[i] = NULL;
	return (ret);
}
