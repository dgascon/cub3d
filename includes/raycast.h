/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   raycast.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/13 11:52:37 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/16 21:38:51 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H
# include "cube3d.h"

typedef struct s_data t_data;

typedef struct  s_raycast
{
	int		column;
	double	alpha;
	double	dist;
}               t_raycast;

double	linear_intersec_h(t_data *data);
double	linear_intersec_v(t_data *data);
double	shortest_dist(t_data *data, double horizontal, double vertical);
#endif