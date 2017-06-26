/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 16:18:32 by nmayfiel          #+#    #+#             */
/*   Updated: 2016/11/23 18:35:47 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

char	*ft_strnew(size_t size)
{
	char *str;

	str = (char *)malloc(size + 1);
	if (!str)
		return (NULL);
	else
		ft_memset(str, '\0', size + 1);
	return (str);
}
