/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:48:59 by dgascon           #+#    #+#             */
/*   Updated: 2020/05/01 10:22:35 by dgascon          ###   ########lyon.fr   */
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
	int		j;
	t_world	*world;
	int		*tmpleny;

	j = -1;
	world = &data->world;
	if (!(tmpleny = wrmalloc(sizeof(int *) * (world->size.y))))
		return (ft_msg(TM_ERROR, "Malloc is not possible", 1, YELLOW));
	while (++j < world->size.y - 1)
		tmpleny[j] = world->leny[j];
	tmpleny[j] = (int)ft_strlen(tmp_map[i]);
	(world->size.x < tmpleny[j]) ? world->size.x = tmpleny[j] : 0;
	wrfree(world->leny);
	world->leny = tmpleny;
	j = -1;
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

	i = -1;
	data->world.size.y++;
	if (!(tmp_map = wrmalloc(sizeof(char *) * (data->world.size.y))))
		return (ft_msg(TM_ERROR, "Malloc is not possible", 1, YELLOW));
	while (++i < data->world.size.y - 1)
	{
		if (!(tmp_map[i] = ft_strdup(data->world.map[i])))
			return (ft_msg(TM_ERROR, "Parsing failed", EXIT_FAILURE, RED));
	}
	tmp_map[i] = line;
	(data->world.size.y > 1) ? wrfree(data->world.map[0]) : 0;
	wrfree(data->world.map);
	data->world.map = tmp_map;
	if (parse_map_2(data, line, tmp_map, i))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
