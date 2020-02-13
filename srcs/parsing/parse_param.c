/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_param.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/13 14:32:18 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/13 14:33:48 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_set_resolu(t_data *data, char **line)
{
	if (!ft_strcmp(line[0], "R"))
	{
		if (data->screen.size.x == 0 && data->screen.size.y == 0)
		{
			if (!line[2])
				return (ft_message(TM_ERROR, "Resolution x, y manquante.",
					1, RED));
			data->screen.size.x = ft_atoi(line[1]);
			data->screen.size.y = ft_atoi(line[2]);
			(data->screen.size.x >= 2560) ? data->screen.size.x = 2559 : 0;
			(data->screen.size.y >= 1440) ? data->screen.size.y = 1439 : 0;
			if (init_window(data))
				return (EXIT_FAILURE);
		}
		else
			return (ft_message(TM_ERROR, "Double arguments", 1, RED));
	}
	return (EXIT_SUCCESS);
}

int parse_set_tex(t_data *data, char **line, t_gnl gnl)
{
	if (flaginit_tex(data, !ft_strcmp(line[0], "F"), &data->w_tex[4], line[1]))
			return (EXIT_FAILURE);
	else if (flaginit_tex(data, !ft_strcmp(line[0], "C"), &data->w_tex[5],
				line[1]))
			return (EXIT_FAILURE);
	else if (flaginit_tex(data, !ft_strcmp(line[0], "NO"), &data->w_tex[0],
				line[1]))
			return (EXIT_FAILURE);
	else if (flaginit_tex(data, !ft_strcmp(line[0], "WE"), &data->w_tex[3],
				line[1]))
			return (EXIT_FAILURE);
	else if (flaginit_tex(data, !ft_strcmp(line[0], "EA"), &data->w_tex[1],
				line[1]))
			return (EXIT_FAILURE);
	else if (flaginit_tex(data, !ft_strcmp(line[0], "V"), &data->hud_tex[0],
				line[1]))
			return (EXIT_FAILURE);
	else if (ft_isdigit(gnl.line[0])
	&& parse_map(data, ft_delcharstr(gnl.line, " ")))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int parse_set_object(t_data *data, char **line)
{
	int indexparam;
	
	if (!ft_strcmp(&line[0][0], "S"))
	{
		indexparam = ft_atoi(&line[0][1]);
		if (ft_digit(indexparam) == 1 && ft_isdigit(line[0][1]))
		{
			if (flaginit_tex(data, indexparam > 2, &data->object[indexparam-3],
				line[1]))
					return (EXIT_FAILURE);
		}
		else if (flaginit_tex(data, line[0][1] == 'O',&data->w_tex[2], line[1]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}