/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_intersec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecaill <nlecaill@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:13:39 by dgascon           #+#    #+#             */
/*   Updated: 2020/02/28 16:28:13 by nlecaill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	linear_intersec_v(t_data *data)
{
	t_coord		grid;
	t_f_coord	intersec;
	t_f_coord	offset;
	t_lsprite	*obj;

	if (data->raycast.alpha > M_PI_2 && data->raycast.alpha < 3 * M_PI_2)
	{
		offset.x = -(BLOCK_SIZE);
		intersec.x = (data->player.pos.x / BLOCK_SIZE) * (BLOCK_SIZE) - 0.001;
	}
	else
	{
		intersec.x = (data->player.pos.x / BLOCK_SIZE) * (BLOCK_SIZE) + BLOCK_SIZE;
		offset.x = BLOCK_SIZE;
	}
	offset.y = offset.x * tanf(data->raycast.alpha);
	intersec.y = data->player.pos.y + ((data->player.pos.x - intersec.x) * tanf(data->raycast.alpha));
	while (1)
	{
		grid.y = intersec.x / BLOCK_SIZE;
		grid.x = intersec.y / BLOCK_SIZE;
		(grid.x < 0) ? grid.x = 0 : 0;
		(grid.x > data->world.size.y - 1) ? grid.x = data->world.size.y - 1 : 0;
		if (data->world.map[grid.x][grid.y] == '1')
		{
			data->raycast.inter.x = intersec.x;
			data->raycast.inter.y = intersec.y;
			return (sqrtf((data->player.pos.x - intersec.x) * (data->player.pos.x - intersec.x)
			+ (data->player.pos.y - intersec.y) * (data->player.pos.y - intersec.y)));
		}
		else if (data->world.map[grid.x][grid.y] > '1')
		{
			obj = pick_object(data->lst, grid);
			if (obj)
			{
				obj->dist = sqrtf((data->player.pos.x - obj->pos.x) * (data->player.pos.x - obj->pos.x)
				+ (data->player.pos.y - obj->pos.y) * (data->player.pos.y - obj->pos.y));
				obj->visible[data->th_num] = 1;
				obj->detect_position.x = intersec.x;
				obj->detect_position.y = intersec.y;
			}
		}
		intersec.x += offset.x;
		intersec.y -= offset.y;
	}
	return (0);
}

float linear_intersec_h(t_data *data)
{
	t_f_coord	intersec;
	t_f_coord	offset;

	offset.x = (float)BLOCK_SIZE / tanf(data->raycast.alpha);
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
	intersec.x = data->player.pos.x + ((data->player.pos.y - intersec.y) / tanf(data->raycast.alpha));
	return (browse_h(data, intersec, offset));
}

float browse_h(t_data *data, t_f_coord intersec, t_f_coord offset)
{
	t_lsprite	*obj;
	t_coord		grid;

	while (1)
	{
		grid.y = intersec.x / BLOCK_SIZE;
		grid.x = intersec.y / BLOCK_SIZE;
		(grid.y < 0) ? grid.y = 0 : 0;
		(grid.y > data->world.size.x - 1) ? grid.y = data->world.size.x - 1 : 0;
		if (data->world.map[grid.x][grid.y] == '1')
		{
			data->raycast.inter_h.x = intersec.x;
			data->raycast.inter_h.y = intersec.y;
			return (sqrtf((data->player.pos.x - intersec.x) * (data->player.pos.x - intersec.x)
			+ (data->player.pos.y - intersec.y) * (data->player.pos.y - intersec.y)));
		}
		else if (data->world.map[grid.x][grid.y] > '1')
		{
			obj = pick_object(data->lst, grid);
			if (obj)
			{
				obj->dist = sqrtf((data->player.pos.x - obj->pos.x) * (data->player.pos.x - obj->pos.x)
				+ (data->player.pos.y - obj->pos.y) * (data->player.pos.y - obj->pos.y));
				obj->visible[data->th_num] = 1;
				obj->detect_position.x = intersec.x;
				obj->detect_position.y = intersec.y;
			}
		}
		intersec.x += offset.x;
		intersec.y += offset.y;
	}
	return (0);
}
