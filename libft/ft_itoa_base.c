/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 14:44:11 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/01/13 14:44:15 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_numlen_base(int value, int base)
{
	int			len;

	len = 0;
	if ((value < 0 && base == 10) || value == 0)
		len++;
	while (value != 0)
	{
		len++;
		value = value / base;
	}
	return (len);
}

char		*ft_itoa_base(int value, int base)
{
	char	*ret;
	int		len;
	int		stop;
	char	*basestr;

	if (base < 2 || base > 36)
		return (NULL);
	basestr = ft_strdup("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	stop = 0;
	len = ft_numlen_base(value, base);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (value < 0 && base == 10)
	{
		ret[0] = '-';
		++stop;
	}
	ret[len] = '\0';
	--len;
	while (len >= stop)
	{
		ret[len] = basestr[ft_abs(value % base)];
		value /= base;
		--len;
	}
	return (ret);
}
