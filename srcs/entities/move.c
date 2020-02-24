/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 10:39:59 by dgascon           #+#    #+#             */
/*   Updated: 2020/02/24 14:22:04 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		move_x(t_data *data, int value)
{
	int tmp;
	int block;

	tmp = data->player.pos.x + value;
	if (tmp < (data->world.size.x * BLOCK_SIZE) && tmp > BLOCK_SIZE)
	{
		block = data->world.map[data->player.pos.y / BLOCK_SIZE]
					[tmp / BLOCK_SIZE];
		if (block >= '2' && !data->object[block - '2'].valid)
		{
			data->world.map[data->player.pos.y / BLOCK_SIZE]
				[tmp / BLOCK_SIZE] = '0';
		}
		if (!(block >= '1' && block <= '2'))
			data->player.pos.x = tmp;
	}
	return (0);
}

int		move_y(t_data *data, float value)
{
	float	tmp;
	int		block;

	tmp = data->player.pos.y + value;
	if (tmp < (data->world.size.y * BLOCK_SIZE) && tmp > BLOCK_SIZE)
	{
		block = data->world.map[(int)(tmp / BLOCK_SIZE)]
					[data->player.pos.x / BLOCK_SIZE];
		if (block >= '2' && !data->object[block - '2'].valid)
		{
			data->world.map[(int)(tmp / BLOCK_SIZE)]
				[data->player.pos.x / BLOCK_SIZE] = '0';
		}
		if (!(block >= '1' && block <= '2'))
			data->player.pos.y = tmp;
	}
	return (0);
}

void	move(t_data *data, float direction)
{
	move_x(data, cosf(direction) * data->player.speed / 2);
	move_y(data, sinf(direction) * -data->player.speed / 2);
}
