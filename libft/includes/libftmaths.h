/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libftmaths.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/20 18:32:02 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/09 22:16:03 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LIBFTMATHS_H
# define LIBFTMATHS_H

typedef struct	s_coord
{
	int		x;
	int		y;
}				t_coord;

int	ft_power(int nb, int power);
int	ft_sqrt(int nb);
int	ft_abs(int val);
#endif
