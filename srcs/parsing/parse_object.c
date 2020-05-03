/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:27:28 by dgascon           #+#    #+#             */
/*   Updated: 2020/05/03 15:44:19 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parse_set_object(t_data *data, char **line)
{
	int indexparam;

	if (data->world.map)
		return (ft_msg(TM_ERROR, "The map must be defined last.", 1, RED));
	indexparam = ft_atoi(&line[0][1]);
	if (ft_strcmp(*line, "SO") == 0)
		return (dup_path(&data->w_tex[2], line[1]));
	else if (ft_strcmp(*line, "S") == 0)
		return (dup_path(&data->obj_tex[0], line[1]));
	else if (ft_isdigit(line[0][1]) && !((int)ft_strlen(*line) > 2))
	{
		if (ft_digit(indexparam) != 1 || (indexparam < 2 || indexparam > 9))
		{
			return (ft_msg(TM_ERROR, ft_strmjoin("sds",
				"Index must be between 2 and 9, it is currently at ",
				indexparam, "."), 1, RED));
		}
		return (dup_path(&data->obj_tex[indexparam - 2], line[1]));
	}
	else
		return (ft_msg(TM_ERROR, "Bad param format (1)", 1, RED));
	return (EXIT_SUCCESS);
}
