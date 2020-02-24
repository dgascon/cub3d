/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:32:18 by dgascon           #+#    #+#             */
/*   Updated: 2020/02/24 17:07:20 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**parse_color(char **line)
{
	char	**tmp;
	char	*tmpline;
	int		i;

	i = 1;
	while (line[++i])
	{
		if (!(tmpline = ft_strjoin(line[1], line[i])))
			return (NULL);
		wrfree(line[1]);
		line[1] = tmpline;
	}
	if (!(tmp = ft_split(line[1], ',')))
		return (NULL);
	return (tmp);
}

static int	parse_floor_ceil3(t_data *data, char **tmp, char state)
{
	int		i;
	int		val;

	i = 0;
	while (*tmp)
	{
		val = ft_atoi(*tmp);
		if (val >= 0 && val <= 255)
		{
			if (state == 'F')
			{
				data->screen.floor_color[i++] = val;
				data->screen.floor_tex = 0;
			}
			else if (state == 'C')
			{
				data->screen.sky_color[i++] = val;
				data->screen.ceil_tex = 0;
			}
		}
		else
			return (ft_msg(TM_ERROR, "Bad format colors !", 1, RED));
		tmp++;
	}
	return (EXIT_SUCCESS);
}

static int	parse_floor_ceil2(t_data *data, char **line, char state)
{
	int		i;
	char	**tmp;

	i = (state == 'F') ? 4 : 5;
	if (ft_isdigit(line[1][0]))
	{
		if (!(tmp = parse_color(line)))
			return (ft_msg(TM_ERROR, "Malloc is not possible", 1, YELLOW));
		return (parse_floor_ceil3(data, tmp, state));
	}
	else
	{
		if (init_texture(data, &data->w_tex[i], line[1]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int			parse_floor_ceil(t_data *data, char **line)
{
	if (!(ft_strcmp(line[0], "F")))
	{
		if (data->screen.flag_floor)
			return (ft_msg(TM_ERROR, "Double argument to floor", 1, RED));
		data->screen.flag_floor = 1;
		if (parse_floor_ceil2(data, line, 'F'))
			return (EXIT_FAILURE);
	}
	else if (!(ft_strcmp(line[0], "C")))
	{
		if (data->screen.flag_ceil)
			return (ft_msg(TM_ERROR, "Double argument to ceil", 1, RED));
		data->screen.flag_ceil = 1;
		if (parse_floor_ceil2(data, line, 'C'))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
