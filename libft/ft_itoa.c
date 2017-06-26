/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 18:21:42 by nmayfiel          #+#    #+#             */
/*   Updated: 2016/12/09 20:25:05 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_itoa(int n)
{
	char		*str;
	size_t		num_chars;

	num_chars = ft_numlen(n);
	str = (char *)malloc(sizeof(char) * (num_chars + 1));
	if (!str)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	if (n == 0)
		str[0] = '0';
	str[num_chars] = '\0';
	num_chars--;
	while (n != 0)
	{
		str[num_chars] = ft_abs(n % 10) + '0';
		n /= 10;
		num_chars--;
	}
	return (str);
}
