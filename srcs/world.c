/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:48:59 by dgascon           #+#    #+#             */
/*   Updated: 2020/02/24 16:36:45 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_map_2(t_data *data, char *line, char **tmp_map, int i)
{
	int j;

	j = 0;
	if (data->world.size.x == 0)
		data->world.size.x = ft_strlen(tmp_map[i]);
	else if (data->world.size.x != (int)ft_strlen(tmp_map[i]))
		return (ft_msg(TM_ERROR, "Map not compliant !", 1, RED));
	while (line[j])
	{
		if (ft_charstr(line[j], "NSWE"))
		{
			if (parse_player(data, line[j],
				(t_coord) {.x = j, .y = data->world.size.y}) <= 0)
				return (EXIT_FAILURE);
		}
		else if (line[j] >= '2')
		{
			if (data->object[line[j] - '2'].valid)
			{
				lsprite_addback(&data->lst, lsprite_new(
				(t_coord){.x = j, .y = data->world.size.y - 1},
				data->object[line[j] - '2']));
			}
		}
		j++;
	}
	return (EXIT_SUCCESS);
}

int			parse_map(t_data *data, char *line)
{
	char	**tmp_map;
	int		i;

	i = 0;
	if (!line)
		return (EXIT_FAILURE);
	data->world.size.y++;
	if (!(tmp_map = wrmalloc(sizeof(char *) * (data->world.size.y))))
		return (ft_msg(TM_ERROR, "Malloc is not possible", 1, YELLOW));
	while (i < data->world.size.y - 1)
	{
		if (!(tmp_map[i] = ft_substr(data->world.map[i], 0,
								ft_strlen(data->world.map[i]))))
			return (ft_msg(TM_ERROR, "Parsing failed", EXIT_FAILURE, RED));
		i++;
	}
	tmp_map[i] = line;
	(data->world.size.y > 1) ? wrfree(data->world.map[0]) : 0;
	wrfree(data->world.map);
	data->world.map = tmp_map;
	if (parse_map_2(data, line, tmp_map, i))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int			checkmapwall(t_data *data)
{
	int y;
	int x;

	y = -1;
	x = -1;
	while (++y < data->world.size.y)
	{
		x = -1;
		while (++x < data->world.size.x)
		{
			if (y == 0 || y == data->world.size.y - 1
			|| x == 0 || x == data->world.size.x - 1)
			{
				if (data->world.map[y][x] != '1')
				{
					return (ft_msg(TM_ERROR,
						"The map is not surrounded by walls !", 1, RED));
				}
			}
		}
	}
	return (EXIT_SUCCESS);
}
