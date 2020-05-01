/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftenum.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecaill <nlecaill@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:56:07 by dgascon           #+#    #+#             */
/*   Updated: 2020/03/12 17:15:46 by nlecaill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTENUM_H
# define LIBFTENUM_H

enum	e_boolean
{
	TRUE = 1,
	FALSE = 0
};

enum	e_base
{
	BASE10 = 0,
	BASE16U = 1,
	BASE16l = 2,
	BASE8 = 3
};

enum	e_keycode
{
	ARROW_DOWN = 65364,
	ARROW_UP = 65362,
	ARROW_RIGHT = 65363,
	ARROW_LEFT = 65361,
	S = 115,
	W = 119,
	D = 100,
	A = 97,
	Q = 113,
	Z = 122,
	E = 101,
	M = 109,
	LSHIFT = 65505,
	RSHIFT = 65506,
	ESC = 65307,
	F1 = 65470,
	LALT = 65513,
	RALT = 65027,
	SPACE = 32,
	LCTRL = 65507
};

enum	e_type_message
{
	TM_INFO,
	TM_ERROR,
	TM_WARNING
};

char	*ft_sbase(enum e_base b);
int		rgb_int(unsigned char alpha, unsigned char red, unsigned char green,
				unsigned char blue);
int		ft_msg(enum e_type_message e, char *message, int ret, char *colors);
#endif
