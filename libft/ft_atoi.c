/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 17:52:17 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/02/09 09:02:25 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	long int		result;
	int				factor;

	factor = 1;
	result = 0;
	while (ft_isspace(*str))
		str++;
	factor = *str == '-' && ft_isdigit(str[1]) ? -factor : factor;
	str = (*str == '-' || *str == '+') && ft_isdigit(str[1]) ? str + 1 : str;
	while (ft_isdigit(*str))
	{
		result *= 10;
		result += *str - 48;
		str++;
	}
	return ((int)(result * factor));
}
