/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charequ_ci.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:14:30 by nmayfiel          #+#    #+#             */
/*   Updated: 2016/11/14 19:15:01 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

int		ft_charequ_ci(char c1, char c2)
{
	if (ft_tolower(c1) == ft_tolower(c2))
		return (1);
	else
		return (0);
}
