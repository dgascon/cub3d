/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libftenum.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/16 15:56:07 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 18:48:00 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
	ARROW_DOWN = 125,
	ARROW_UP = 126,
	ARROW_RIGHT = 124,
	ARROW_LEFT = 123,
	S = 1,
	W = 13,
	D = 2,
	A = 0,
	Q = 12,
	Z = 6,
	E = 14,
	M = 46,
	LSHIFT = 257,
	RSHIFT = 258,
	ESC = 53,
	F1 = 122,
	LALT = 261,
	RALT = 262,
	SPACE = 49,
	LCTRL = 256
};

char	*ft_sbase(enum e_base b);
int		rgb_int(int red, int green, int blue);
#endif
