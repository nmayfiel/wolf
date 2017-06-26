/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 19:26:00 by nmayfiel          #+#    #+#             */
/*   Updated: 2016/11/08 19:31:37 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_abs(int n)
{
	if (n == -2147483648 || n >= 0)
		return (n);
	if (n < 0)
		return (-n);
	return (0);
}
