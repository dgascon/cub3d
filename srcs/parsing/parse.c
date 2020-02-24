/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:26:22 by dgascon           #+#    #+#             */
/*   Updated: 2020/02/24 16:58:44 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char		**filter(char *line)
{
	char	**tab;
	char	*current;
	int		i;

	i = -1;
	tab = ft_split(line, ' ');
	while (tab[++i])
	{
		current = ft_delcharstr(tab[i], " ");
		wrfree(tab[i]);
		tab[i] = current;
	}
	return (tab);
}

static int	parseparam(t_data *data, char **line, t_gnl gnl)
{
	if (!ft_strcmp(line[0], "R"))
	{
		return (parse_set_resolu(data, line));
	}
	else if (!ft_strcmp(&line[0][0], "S"))
	{
		return (parse_set_object(data, line));
	}
	else if (ft_isdigit(gnl.line[0]))
	{
		return (parse_map(data, ft_delcharstr(gnl.line, " ")));
	}
	else if (parse_set_tex(data, line))
	{
		
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	checkerror(t_data *data)
{
	if (data->screen.size.x == 0 && data->screen.size.y == 0)
		return (ft_msg(TM_ERROR, "Resolution is not defined !", 1, RED));
	if (data->player.pos.x == 0 && data->player.pos.y == 0)
		return (ft_msg(TM_ERROR, "No player in map.", 1, RED));
	if (!data->screen.flag_ceil || !data->screen.flag_floor)
		return (ft_msg(TM_ERROR, "Floor or/and Ceil not defined.", 1, RED));
	if (data->screen.floor_tex != data->screen.ceil_tex)
		return (ft_msg(TM_ERROR, "Floor or/and Ceil is different !", 1, RED));
	if (checkmapwall(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int			parsefile(t_data *data, char *file)
{
	t_gnl	gnl;
	char	**cur_line;

	gnl = (t_gnl) {.fd = -1, .line = NULL, .ret = -1};
	data->world.size = (t_coord) {.x = 0, .y = 0};
	data->screen.floor_tex = 1;
	data->screen.ceil_tex = 1;
	if (checkformatfile(file, &gnl, ".cub"))
		return (EXIT_FAILURE);
	while (1)
	{
		gnl.ret = get_next_line(gnl.fd, &gnl.line);
		cur_line = filter(gnl.line);
		if (cur_line[0])
		{
			if (parseparam(data, cur_line, gnl))
				return (EXIT_FAILURE);
		}
		wrfree(gnl.line);
		splitfree(cur_line);
		if (gnl.ret <= 0)
			break ;
	}
	close(gnl.fd);
	return (checkerror(data));
}
