/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:08:05 by dgascon           #+#    #+#             */
/*   Updated: 2020/02/24 16:26:39 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parse_player(t_data *data, char direction, t_coord position)
{
	if (data->player.pos.x != 0 && data->player.pos.y != 0)
	{
		ft_printf("Two player placed on the map\n");
		wrdestroy();
		return (-1);
	}
	if (direction == 'N')
		data->player.pov = M_PI / 2;
	else if (direction == 'E')
		data->player.pov = 2 * M_PI;
	else if (direction == 'S')
		data->player.pov = 3 * M_PI_2;
	else if (direction == 'W')
		data->player.pov = M_PI;
	data->player.pos.x = (BLOCK_SIZE * position.x) + BLOCK_SIZE / 2;
	data->player.pos.y = (BLOCK_SIZE * position.y) - BLOCK_SIZE / 2;
	return (1);
}
