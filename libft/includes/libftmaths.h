/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libftmaths.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/20 18:32:02 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/17 16:54:34 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LIBFTMATHS_H
# define LIBFTMATHS_H

typedef struct	s_coord
{
	double	x;
	double	y;
}				t_coord;

int		ft_power(int nb, int power);
int		ft_sqrt(int nb);
double	ft_abs_d(double val);
#endif
