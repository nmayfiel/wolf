/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 21:00:26 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/05/14 21:00:34 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

void	print_usage(char *name)
{
	ft_putstr("Usage:\t");
	ft_putstr(name);
	ft_putstr(" julia|mandelbrot|ship [-o opencl]\n");
	exit(0);
}

/* else if (error_code == E_BADFILE)
 * perror(NULL);
 * else if (error_code == E_BADFORM)
 * ft_putendl_fd(EMSG_BADFORM, 2);
 * else if (error_code == E_MALLOC)
 * perror(NULL);
*/

void	exit_error(int32_t error_code)
{
	(void)error_code;
	exit(0);
}
