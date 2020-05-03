/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 16:00:41 by dgascon           #+#    #+#             */
/*   Updated: 2020/05/03 15:44:35 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	int	checkresol(char *line)
{
	int i;

	i = -1;
	while (line[++i])
	{
		if (!ft_isdigit(line[i]))
			return (ft_msg(TM_ERROR, "Bad value for resolution. (4)", 1, RED));
	}
	return (EXIT_SUCCESS);
}

int			parse_set_resolu(t_data *data, char **line)
{
	if (ft_strcmp(*line, "R"))
		return (ft_msg(TM_ERROR, "Bad Param format", 1, RED));
	if (data->world.map)
		return (ft_msg(TM_ERROR, "The map must be defined last.", 1, RED));
	if (data->screen.size.x == 0 && data->screen.size.y == 0)
	{
		if (!line[2] || !line[1])
			return (ft_msg(TM_ERROR, "Resolution x, y is missing", 1, RED));
		if (checkresol(line[1]) || checkresol(line[2]))
			return (EXIT_FAILURE);
		data->screen.size.x = ft_atoi(line[1]);
		data->screen.size.y = ft_atoi(line[2]);
		if (data->screen.size.x <= 0 || data->screen.size.y <= 0)
			return (ft_msg(TM_ERROR, "Resolution too small", 1, RED));
	}
	else
		return (ft_msg(TM_ERROR, "Double argument to parsing", 1, RED));
	return (0);
}
