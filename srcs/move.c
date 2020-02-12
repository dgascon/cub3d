/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/12 15:42:01 by nlecaill     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/12 17:18:00 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int		move_x(t_data *data, int value)
{
	int tmp;

	tmp = data->player.pos.x + value;
	if (tmp < (data->world.size.x * BLOCK_SIZE) &&	tmp > BLOCK_SIZE)
	{
		if (!(data->world.map[data->player.pos.y / BLOCK_SIZE][tmp / BLOCK_SIZE] >= '1'
		&& data->world.map[data->player.pos.y / BLOCK_SIZE][tmp / BLOCK_SIZE] <= '3'))
			data->player.pos.x = tmp;
		else if (data->world.map[data->player.pos.y / BLOCK_SIZE][tmp / BLOCK_SIZE] == '2'
		&& data->world.locked == 0)
			data->player.pos.x = tmp;
	}
	return (0);
}

int		move_y(t_data *data, float value)
{
	float tmp;

	tmp = data->player.pos.y + value;
	if (tmp < (data->world.size.y * BLOCK_SIZE) &&	tmp > BLOCK_SIZE)
	{
		if (!(data->world.map[(int)(tmp / BLOCK_SIZE)][data->player.pos.x / BLOCK_SIZE] >= '1'
		&& data->world.map[(int)(tmp / BLOCK_SIZE)][data->player.pos.x / BLOCK_SIZE] <= '3'))
			data->player.pos.y = tmp;
		else if (data->world.map[(int)(tmp / BLOCK_SIZE)][data->player.pos.x / BLOCK_SIZE] == '2' && data->world.locked == 0)
			data->player.pos.y = tmp;
	}
	return (0);
}

void	move(t_data *data, float direction)
{
	move_x(data, cosf(direction) * data->player.speed);
	move_y(data, sinf(direction) * -data->player.speed);
}
