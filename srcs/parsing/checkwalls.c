/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkwalls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 18:01:08 by dgascon           #+#    #+#             */
/*   Updated: 2020/05/01 10:22:15 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	checkwall(t_world *world, int csize, int y, int x)
{
	char	around[4];
	int		i;

	i = -1;
	ft_bzero(around, 4);
	(y > 0) ? around[0] = world->map[y - 1][x] : 0;
	(y < world->size.y - 1) ? around[1] = world->map[y + 1][x] : 0;
	(x > 0) ? around[2] = world->map[y][x - 1] : 0;
	(x < csize - 1) ? around[3] = world->map[y][x + 1] : 0;
	if (ft_charstr(world->map[y][x], "NSEW023456789"))
	{
		while (++i < 4)
		{
			if (around[i] == ' ')
			{
				if (ft_charstr(world->map[y][x], "NSEW"))
					return (ft_msg(TM_ERROR, "Player in void !", 1, RED));
				if (world->map[y][x] >= '2' && world->map[y][x] <= '9')
					return (ft_msg(TM_ERROR, "Object in void !", 1, RED));
				return (ft_msg(TM_ERROR,
				"The map is not surrounded by walls (1)!", 1, RED));
			}
		}
	}
	return (EXIT_SUCCESS);
}

static	int	checkwalls(t_world *world, int csize, int y)
{
	t_coord	onsize;
	t_coord	ondiff;
	int		i;

	i = 0;
	if (y > 0 && y < world->size.y - 1)
	{
		onsize.x = world->leny[y - 1];
		onsize.y = world->leny[y + 1];
		if (onsize.y < csize || onsize.x > csize)
			return (EXIT_SUCCESS);
		while (world->map[y][csize - i - 1] == '1')
			i++;
		ondiff.x = (csize - i) - onsize.x + 1;
		ondiff.y = (csize - i) - onsize.y + 1;
		if (ondiff.x > 1 || ondiff.y > 1)
			return (ft_msg(TM_ERROR,
				"The map is not surrounded by walls (2)!", 1, RED));
	}
	return (EXIT_SUCCESS);
}

int			checkmapwall(t_data *data)
{
	t_coord	ind;
	int		csize;
	char	block;

	ind = (t_coord) {-1, -1};
	while (++ind.y < data->world.size.y)
	{
		ind.x = -1;
		csize = data->world.leny[ind.y];
		while (++ind.x < csize)
		{
			block = data->world.map[ind.y][ind.x];
			if ((ind.y == 0 || ind.y == data->world.size.y - 1 || ind.x == 0 ||
				ind.x == csize - 1) && !ft_charstr(block, "1 "))
			{
				return (ft_msg(TM_ERROR,
					"The map is not surrounded by walls (3)!", 1, RED));
			}
			if (checkwall(&data->world, csize, ind.y, ind.x))
				return (EXIT_FAILURE);
		}
		if (checkwalls(&data->world, csize, ind.y))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
