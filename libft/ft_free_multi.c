/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_multi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 01:14:07 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/06/14 01:36:55 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <stdlib.h>

void	ft_free_multi(int num, ...)
{
	va_list	valist;
	int		i;

	va_start(valist, num);
	i = 0;
	while (i < num)
	{
		free(va_arg(valist, void *));
		++i;
	}
	va_end(valist);
}
