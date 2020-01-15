/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libftenum.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/16 15:56:07 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/17 19:16:46 by dgascon     ###    #+. /#+    ###.fr     */
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

char			*ft_sbase(enum e_base b);

#endif
