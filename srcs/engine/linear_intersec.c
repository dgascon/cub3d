/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   linear_intersec.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 18:13:39 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/21 07:48:05 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

double linear_intersec_v(t_data *data)
{
	t_coord grid;
	t_d_coord intersec;
	t_d_coord offset;

	if (data->raycast.alpha > M_PI_2 && data->raycast.alpha < 3 * M_PI_2)
	{
		offset.x = -(BLOCK_SIZE);
		intersec.x = (data->player.pos.x / BLOCK_SIZE) * (BLOCK_SIZE) - 0.001;//REVIEW CHECK FNCT FLOOR
	}
	else
	{
		intersec.x = (data->player.pos.x / BLOCK_SIZE) * (BLOCK_SIZE) + BLOCK_SIZE;
		offset.x = BLOCK_SIZE;
	}
	offset.y = offset.x * tan(data->raycast.alpha);
	intersec.y = data->player.pos.y + ((data->player.pos.x - intersec.x) * tan(data->raycast.alpha));
	while (1)
	{
		grid.y = floor(intersec.x / BLOCK_SIZE);
		grid.x = floor(intersec.y / BLOCK_SIZE);
		// if (grid.y < 0)
		// 	grid.y = 0;
		if (grid.x < 0)
			grid.x = 0;
		// if (grid.y > data->world.size.x - 1)
		// 	grid.y = data->world.size.x - 1;
		if (grid.x > data->world.size.y - 1)
			grid.x = data->world.size.y - 1;
		if (data->world.map[grid.x][grid.y] == '1')
		{
			data->raycast.inter.x = intersec.x;
			data->raycast.inter.y = intersec.y;
			return(sqrt(pow(data->player.pos.x - intersec.x, 2) +
						 pow(data->player.pos.y - intersec.y, 2))); //REVIEW Passer par les ABS
		}
		intersec.x += offset.x;
		intersec.y -= offset.y;
	}
	return (0);
}

double linear_intersec_h(t_data *data)
{
	t_d_coord	intersec;
	t_d_coord	offset;
	t_coord		grid;

	offset.x = BLOCK_SIZE / tan(data->raycast.alpha); // REVIEW optimisation
	if (data->raycast.alpha > 0 && data->raycast.alpha < M_PI)
	{
		intersec.y = (data->player.pos.y / BLOCK_SIZE) * (BLOCK_SIZE) - 0.001;
		offset.y = -(BLOCK_SIZE);
	}
	else
	{
		intersec.y = (data->player.pos.y / BLOCK_SIZE) * BLOCK_SIZE + BLOCK_SIZE;
		offset.y = BLOCK_SIZE;
		offset.x *= -1;
	}
	intersec.x = data->player.pos.x + ((data->player.pos.y - intersec.y) / tan(data->raycast.alpha));
	while (1)
	{
		grid.y = floor(intersec.x / BLOCK_SIZE);
		grid.x = floor(intersec.y / BLOCK_SIZE);
		(grid.y < 0) ? grid.y = 0 : 0;
		// (grid.x < 0) ? grid.x = 0 : 0;
		(grid.y > data->world.size.x - 1) ? grid.y = data->world.size.x - 1 : 0;
		// (grid.x > data->world.size.y - 1) ? grid.x = data->world.size.y - 1 : 0;
		if (data->world.map[grid.x][grid.y] == '1')
		{
			data->raycast.interH.x = intersec.x;
			data->raycast.interH.y = intersec.y;
			return (sqrt(pow(data->player.pos.x - intersec.x, 2) +
						 pow(data->player.pos.y - intersec.y, 2))); //REVIEW Passer par les ABS
		}
		intersec.x += offset.x;
		intersec.y += offset.y;
	}
	return (0);
}