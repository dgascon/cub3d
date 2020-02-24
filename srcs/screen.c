/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 16:00:41 by dgascon           #+#    #+#             */
/*   Updated: 2020/02/24 16:26:51 by dgascon          ###   ########lyon.fr   */
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
			return (ft_msg(TM_ERROR, "Bad value for resolution.", 1, RED));
	}
	return (EXIT_SUCCESS);
}

int			parse_set_resolu(t_data *data, char **line)
{
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
		(data->screen.size.x >= 2560) ? data->screen.size.x = 2559 : 0;
		(data->screen.size.y >= 1440) ? data->screen.size.y = 1439 : 0;
		if (init_window(data))
			return (EXIT_FAILURE);
	}
	else
		return (ft_msg(TM_ERROR, "Double argument to parsing", 1, RED));
	return (ft_msg(TM_INFO, "Resolution set.", 0, GREEN));
}
