/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   raycast.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/13 11:52:37 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/13 14:54:13 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H
# include "cube3d.h"

typedef struct  s_raycast
{
	int		column;
	double	alpha;
	double	dist;
}               t_raycast;
#endif