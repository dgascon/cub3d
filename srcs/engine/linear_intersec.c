/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   linear_intersec.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 14:42:43 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/16 00:15:31 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cube3d.h"

double		linear_intersec_h(t_world *world, t_raycast *ray)
{
	t_coord intersec;
	t_coord offset;
	double	beta;
	double	dist;

	printf("Alpha H : %f\n", ray->alpha);
	if (ray->alpha > 0 && ray->alpha < M_PI)
	{
		intersec.y = round(world->player.coord.y / 64) * (64) - 1;
		offset.y = -64;
	}
	else
	{
		intersec.y = round(world->player.coord.y / 64) * (64) + 64;
		offset.y = 64;
	}
	intersec.x = world->player.coord.x + (world->player.coord.y - intersec.y) / tan(ray->alpha);
	offset.x = 64 / tan(ray->alpha);
	while (world->data[intersec.x / 64][intersec.y / 64] != '1')	
	{
		intersec.x += offset.x;
		intersec.y += offset.y; 
	}
	beta = ray->alpha - world->player.pov;
	dist = ft_abs(world->player.coord.x - intersec.x) / cos(ray->alpha);
	if (ray->alpha < world->player.pov)
		dist = dist * cos(beta);
	else
		dist = dist * cos(-beta);
	return (dist);
}

double		linear_intersec_v(t_world *world, t_raycast *ray)
{
	t_coord intersec;
	t_coord offset;
	double	beta;
	double	dist;

	if (ray->alpha > M_PI_2 && ray->alpha < ((3 * M_PI) / 2))
	{
		intersec.x = round(world->player.coord.x / 64) * (64) - 1;
		offset.x = -64;
	}
	else
	{
		intersec.x = round(world->player.coord.x / 64) * (64) + 64;
		offset.x = 64;
	}
	intersec.y = world->player.coord.y + (world->player.coord.x - intersec.x) * tan(ray->alpha);
	offset.y = 64 * tan(ray->alpha);
	printf("[%d][%d] | [%d][%d]", intersec.x, intersec.y, intersec.x / 64, intersec.y / 64);
	while (world->data[intersec.x / 64][intersec.y / 64] != '1')
	{
		intersec.x += offset.x;
		intersec.y += offset.y;
	}
	beta = ray->alpha - world->player.pov;
	dist = ft_abs(world->player.coord.x - intersec.x) / cos(ray->alpha);
	if (ray->alpha < world->player.pov)
		dist = dist * cos(beta);
	else
		dist = dist * cos(-beta);
	return (dist);
}

double		shortest_dist(double horizontal, double vertical)
{
	return (horizontal < vertical) ? horizontal : vertical;
}