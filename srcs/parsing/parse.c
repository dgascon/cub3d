/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:26:22 by dgascon           #+#    #+#             */
/*   Updated: 2020/02/17 12:22:22 by dgascon          ###   ########lyon.fr   */
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
	if (parse_set_resolu(data, line))
		return (EXIT_FAILURE);
	else if (data->screen.size.x == 0 && data->screen.size.y == 0)
		return (ft_msg(TM_ERROR, "Resolution is not defined !",
			1, RED));
	else if (parse_set_object(data, line))
		return (EXIT_FAILURE);
	else if (parse_set_tex(data, line, gnl))
		return (EXIT_FAILURE);
	else if (ft_isdigit(gnl.line[0])
	&& parse_map(data, ft_delcharstr(gnl.line, " ")))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int			parsefile(t_data *data, char *file)
{
	t_gnl	gnl;
	char	**cur_line;

	gnl = (t_gnl) {.fd = -1, .line = NULL, .ret = -1};
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
	if (data->player.pos.x == 0 && data->player.pos.y == 0)
		return (ft_msg(TM_ERROR, "No player in map.", 1, RED));
	return (EXIT_SUCCESS);
}
