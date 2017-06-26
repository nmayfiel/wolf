/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 14:44:43 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/01/13 14:48:58 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void		print_charvals(unsigned char *arr, int start, size_t size)
{
	int		i;

	i = start;
	while (i < start + 16 && (size_t)i < size)
	{
		if (arr[i] > ' ' && arr[i] <= '~')
			write(1, &arr[i], 1);
		else
			write(1, ".", 1);
		++i;
	}
	write(1, "\n", 1);
}

static void		print_memline(unsigned char *arr, int i, size_t size)
{
	char	*base;

	base = ft_strdup("0123456789abcdef");
	write(1, &base[(arr[i] / 16)], 1);
	write(1, &base[(arr[i] % 16)], 1);
	if ((i + 1) % 2 == 0)
		write(1, " ", 1);
	if ((i + 1) % 16 == 0)
		print_charvals(arr, i - 15, size);
}

static void		fill_spaces(unsigned char *arr, int i, size_t size)
{
	while ((i + 1) % 16 != 0)
	{
		if (i % 2 == 0)
			write(1, " ", 1);
		write(1, "  ", 2);
		++i;
	}
	print_charvals(arr, i - 15, size);
}

void			ft_print_memory(const void *addr, size_t size)
{
	int				i;
	unsigned char	*arr;

	i = 0;
	arr = (unsigned char *)addr;
	while ((size_t)i < size)
	{
		print_memline(arr, i, size);
		++i;
	}
	if (i % 16 != 0)
		fill_spaces(arr, i - 1, size);
}
