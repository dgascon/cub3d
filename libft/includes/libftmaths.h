/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libftmaths.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nlecaill <nlecaill@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 02:52:48 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/12 13:25:54 by nlecaill    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LIBFTMATHS_H
# define LIBFTMATHS_H
# define _2PI 2*3.14159265359f
# define _3PI2 3*1.57079632679f

typedef struct	s_coord
{
	int x;
	int y;
}				t_coord;

typedef struct	s_d_coord
{
	double	x;
	double	y;
}				t_d_coord;

typedef struct	s_f_coord
{
	float	x;
	float	y;
}				t_f_coord;

int				ft_power(int nb, int power);
int				ft_sqrt(int nb);
double			ft_abs_d(double val);
#endif
