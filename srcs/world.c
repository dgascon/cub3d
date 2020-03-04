/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:48:59 by dgascon           #+#    #+#             */
/*   Updated: 2020/03/04 22:22:52 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int fillmap(t_data *data)
{
	int		x;
	int		y;
	int		size;
	char	*tmp;

	x = -1;
	y = -1;
	while (++y < data->world.size.y)
	{
		size = ft_strlen(data->world.map[y]);
		x = -1;
		if (size != data->world.size.x)
		{
			x += ft_strlen(data->world.map[y]);
			while (++x < data->world.size.x)
			{
				tmp = NULL;
				if (!(tmp = ft_strjoin(data->world.map[y], " ")))
					return (ft_msg(TM_ERROR, "Bad Malloc !", 1, RED));
				wrfree(data->world.map[y]);
				data->world.map[y] = tmp;
			}
		}
	}
	return (EXIT_SUCCESS);
}

static int	parse_map_2(t_data *data, char *line, char **tmp_map, int i)
{
	int j;
	int	tmp;

	j = 0;
	tmp = ft_strlen(tmp_map[i]);
	(data->world.size.x < tmp) ? data->world.size.x = tmp : 0;
	while (line[j])
	{
		if (ft_charstr(line[j], "NSWE"))
		{
			if (parse_player(data, line[j],
				(t_coord) {.x = j, .y = data->world.size.y}))
				return (EXIT_FAILURE);
		}
		else if (line[j] >= '2')
		{
			if (data->obj_tex[line[j] - '2'].valid)
			{
				lsprite_addback(&data->lst, lsprite_new(
				(t_coord){.x = j, .y = data->world.size.y - 1},
				data->obj_tex[line[j] - '2']));
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
		if (!(tmp_map[i] = ft_substr(data->world.map[i], 0, //REVIEW strdup ?
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

static int checkwall(t_world *world, int csize, int y, int x)
{
	char around[4]; //REVIEW UP 0, DOWN 1, LEFT 2, RIGHT 3
	int i;

	i = -1;
	around[0] = '\0';
	around[1] = '\0';
	around[2] = '\0';
	around[3] = '\0';

	if (y > 0 && world->map[y - 1][x])
		around[0] = world->map[y - 1][x];
	if (y < world->size.y - 1 && world->map[y + 1][x])
		around[1] = world->map[y + 1][x];
	if (x > 0)
		around[2] = world->map[y][x - 1];
	if (x < csize - 1)
		around[3] = world->map[y][x + 1];
	if (world->map[y][x] == '0')
	{
		while (++i < 4)
		{
			if (around[i] == ' ')
			{
				return (ft_msg(TM_ERROR,
				"The map is not surrounded by walls (1)!", 1, RED));
			}
		}	
	}
	return (EXIT_SUCCESS);
}

static	int	checkwalls(t_world *world, int csize, int y)
{
	t_coord onsize;
	t_coord ondiff;
	int i;

	i = 0;
	if (y > 0 && y < world->size.y - 1)
	{
		onsize.x = ft_strlen(world->map[y - 1]);
		onsize.y = ft_strlen(world->map[y + 1]);
		while (world->map[y][csize - i - 1] == '1')
			i++;
		ondiff.x = (csize - i) - onsize.x + 1;
		ondiff.y = (csize - i) - onsize.y + 1;
		if (ondiff.x > 1 || ondiff.y > 1)
		{
			return (ft_msg(TM_ERROR,
				"The map is not surrounded by walls (2)!", 1, RED));
		}
	}
	return (EXIT_SUCCESS);
}

int			checkmapwall(t_data *data)
{
	int y;
	int x;
	int csize;
	int flag;

	y = -1;
	x = -1;
	flag = 0;
	while (++y < data->world.size.y)
	{
		x = -1;
		csize = ft_strlen(data->world.map[y]);
		while (++x < csize)
		{
			if (checkwall(&data->world, csize, y, x))
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
