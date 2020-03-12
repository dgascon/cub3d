/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:48:59 by dgascon           #+#    #+#             */
/*   Updated: 2020/03/12 09:54:22 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parseplayer_obj(t_data *data, int j, char c)
{
	if (ft_charstr(c, "NSWE"))
	{
		if (parse_player(data, c,
			(t_coord) {.x = j, .y = data->world.size.y}))
			return (EXIT_FAILURE);
	}
	else if (c >= '2')
	{
		if (data->obj_tex[c - '2'].valid)
		{
			lsprite_addback(&data->lst, lsprite_new(
			(t_coord){.x = j, .y = data->world.size.y - 1},
			data->obj_tex[c - '2']));
		}
		else
			return (ft_msg(TM_ERROR, "Texture not assigned !", 1, RED));
	}
	return (EXIT_SUCCESS);
}

static int	parse_map_2(t_data *data, char *line, char **tmp_map, int i)
{
	int j;
	int	tmp;

	j = -1;
	tmp = ft_strlen(tmp_map[i]);
	(data->world.size.x < tmp) ? data->world.size.x = tmp : 0;
	while (line[++j])
	{
		if (!ft_charstr(line[j], "0123456789NSEW "))
			return (ft_msg(TM_ERROR, "Map not compliant.", 1, RED));
		if (parseplayer_obj(data, j, line[j]))
			return (EXIT_FAILURE);
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
		if (!(tmp_map[i] = ft_strdup(data->world.map[i])))
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
