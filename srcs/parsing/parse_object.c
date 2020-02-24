/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:59:10 by dgascon           #+#    #+#             */
/*   Updated: 2020/02/24 16:26:47 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			parse_set_object(t_data *data, char **line)
{
	int indexparam;

	if (data->world.map)
		return (ft_msg(TM_ERROR, "The map must be defined last.", 1, RED));
	indexparam = ft_atoi(&line[0][1]);
	if (ft_digit(indexparam) == 1 && ft_isdigit(line[0][1]))
	{
		if (flaginit_tex(data, indexparam > 2,
			&data->object[indexparam - 2], line[1]))
			return (EXIT_FAILURE);
	}
	else if (line[0][1] == 'O')
	{
		if (flaginit_tex(data, line[0][1] == 'O', &data->w_tex[2], line[1]))
			return (EXIT_FAILURE);
	}
	else
	{
		if (init_texture(data, &data->object[0], line[1]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
