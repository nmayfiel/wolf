/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 13:24:04 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/04/14 11:11:07 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	join = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (NULL);
	while (*(s1 + i) != 0)
		*(join + j++) = *(s1 + i++);
	i = 0;
	while (*(s2 + i) != 0)
		*(join + j++) = *(s2 + i++);
	*(join + j) = '\0';
	return (join);
}
