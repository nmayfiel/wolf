/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmayfiel <nmayfiel@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 10:54:57 by nmayfiel          #+#    #+#             */
/*   Updated: 2017/03/21 10:55:00 by nmayfiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# define KEY_Q		0x0C
# define KEY_W		0x0D
# define KEY_E		0x0E
# define KEY_A		0x00
# define KEY_S		0x01
# define KEY_D		0x02

# define KEY_R		0x0F
# define KEY_T		0x11
# define KEY_Y		0x10
# define KEY_U		0x20
# define KEY_I		0x22
# define KEY_O		0x1F
# define KEY_P		0x23
# define KEY_F		0x03
# define KEY_G		0x05
# define KEY_H		0x04
# define KEY_J		0x26
# define KEY_K		0x28
# define KEY_L		0x25
# define KEY_Z		0x06
# define KEY_X		0x07
# define KEY_C		0x08
# define KEY_V		0x09
# define KEY_B		0x0B
# define KEY_N		0x2D
# define KEY_M		0x2E

# define KEY_UP		0x7E
# define KEY_DOWN	0x7D
# define KEY_RIGHT	0x7C
# define KEY_LEFT	0x7B

# define KEY_ESC		0x35

# define KVAL_UP 	0x01
# define KVAL_DOWN	0x02
# define KVAL_RIGHT	0x04
# define KVAL_LEFT	0x08
# define KVAL_W		0x10
# define KVAL_S		0x20
# define KVAL_A		0x40
# define KVAL_D		0x80
# define KVAL_Q		0x100
# define KVAL_E		0x200
# define KVAL_I 0x400
# define KVAL_J 0x800
# define KVAL_K 0x1000
# define KVAL_L 0x2000
# define KVAL_ESC	0x4000

typedef unsigned int	t_keys;

int						add_key(int keycode, t_keys *keys);
int						remove_key(int keycode, t_keys *keys);

#endif
