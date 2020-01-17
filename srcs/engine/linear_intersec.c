/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   linear_intersec.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 14:42:43 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/17 17:07:02 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cube3d.h"

static double	intersec_check(t_data *data, t_coord intersec, t_coord offset)
{
	t_coord	grid;
	
	grid = (t_coord) {};
	while (1)
	{
		grid.x = round(intersec.x / 64);
		grid.y = round(intersec.y / 64);
		(grid.x > data->world.width) ? grid.x = data->world.width - 1: 0;
		(grid.y > data->world.height) ? grid.y = data->world.height - 1: 0;
		(grid.x < 0) ? grid.x = 0 : 0;
		(grid.y < 0) ? grid.y = 0 : 0;
		if (data->world.map[(int)grid.x][(int)grid.y] == '1')
		{
			printf("Dist : [%f]\t[%f]\n",data->world.player.pos.x - intersec.x, cos(data->world.player.ray.alpha));
			return (ft_abs_d(data->world.player.pos.x - intersec.x) / cos(data->world.player.ray.alpha));
		}
		intersec.x += offset.x;
		intersec.y += offset.y;
	}
	return (-1);
}	

double		linear_intersec_h(t_data *data)
{
	t_coord intersec;
	t_coord offset;

	if (data->world.player.ray.alpha > 0 && data->world.player.ray.alpha < M_PI)
	{
		intersec.y = round(data->world.player.pos.y / 64) * (64) - 0.1;
		offset.y = -64;
	}
	else
	{
		intersec.y = round(data->world.player.pos.y / 64) * (64) + 64;
		offset.y = 64;
	}
	intersec.x = data->world.player.pos.x + round((data->world.player.pos.y - intersec.y) / tan(data->world.player.ray.alpha));
	offset.x = round(64 / tan(data->world.player.ray.alpha));
	return (intersec_check(data, intersec, offset));
}

double		linear_intersec_v(t_data *data)
{
	t_coord intersec;
	t_coord offset;

	if (data->world.player.ray.alpha > M_PI_2 && data->world.player.ray.alpha < ((3 * M_PI) / 2))
	{
		intersec.x = round(data->world.player.pos.x / 64) * (64) - 0.1;
		offset.x = -64;
	}
	else
	{
		intersec.x = round(data->world.player.pos.x / 64) * (64) + 64;
		offset.x = 64;
	}
	intersec.y = data->world.player.pos.y + (data->world.player.pos.x - intersec.x) * tan(data->world.player.ray.alpha);
	offset.y = 64 * tan(data->world.player.ray.alpha);
	return (intersec_check(data, intersec, offset));
}

double		shortest_dist(t_data *data, double horizontal, double vertical)
{
	double beta;
	double short_dist;

	beta = data->world.player.ray.alpha - data->world.player.pov;
	short_dist = (horizontal < vertical) ? horizontal : vertical;
	return ((short_dist * (data->world.player.ray.alpha < data->world.player.pov)) ? cos(beta) : cos(-beta));
}