/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:14:03 by dgascon           #+#    #+#             */
/*   Updated: 2020/05/13 11:20:35 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**filter(t_data *data, char *line)
{
	char	**tab;
	char	*current;
	int		i;
	int		flag;

	i = -1;
	flag = 0;
	(line[0] == ' ') ? flag = 1 : 0;
	tab = ft_split(line, ' ');
	while (tab[++i])
	{
		current = ft_delcharstr(tab[i], " ");
		wrfree(tab[i]);
		tab[i] = current;
		if (flag && (ft_isalpha(tab[0][0]) && !data->world.map))
		{
			ft_msg(TM_ERROR, "Bad param format (0)", 1, RED);
			return (NULL);
		}
	}
	return (tab);
}

static int	parseparam(t_data *data, char **line, t_gnl gnl)
{
	if (line[0][0] == 'R')
		return (parse_set_resolu(data, line));
	else if (line[0][0] == 'S')
		return (parse_set_object(data, line));
	else if (data->world.map || ft_isdigit(line[0][0]))
		return (parse_map(data, ft_strdup(gnl.line)));
	else if (parse_set_tex(data, line))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	checkerror(t_data *data)
{
	int i;

	i = -1;
	if (data->screen.size.x == 0 && data->screen.size.y == 0)
		return (ft_msg(TM_ERROR, "Resolution is not defined !", 1, RED));
	if (data->player.pos.x == 0 && data->player.pos.y == 0)
		return (ft_msg(TM_ERROR, "No player in map.", 1, RED));
	if (!data->screen.flag_ceil || !data->screen.flag_floor)
		return (ft_msg(TM_ERROR, "Floor or/and Ceil not defined.", 1, RED));
	if (data->screen.floor_tex != data->screen.ceil_tex)
		return (ft_msg(TM_ERROR, "Floor or/and Ceil is different !", 1, RED));
	while (++i < 4)
	{
		if (!data->w_tex[i].path)
			return (ft_msg(TM_ERROR, "Texture wall missing !", 1, RED));
	}
	if (checkmapwall(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	load_tex(t_data *data)
{
	int i;
	int max;

	max = 0;
	i = -1;
	if (checkerror(data) || init_window(data))
		return (EXIT_FAILURE);
	(!data->screen.floor_tex || !data->screen.ceil_tex) ? max += 2 : 0;
	while (++i < W_TEX - max)
		if (init_texture(data, &data->w_tex[i]))
			return (EXIT_FAILURE);
	i = -1;
	while (++i < HUD_TEX)
		if (init_texture(data, &data->hud_tex[i]))
			return (EXIT_FAILURE);
	i = -1;
	while (++i < OBJ_TEX)
		if (init_texture(data, &data->obj_tex[i]))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int			parsefile(t_data *data, char *file)
{
	t_gnl	gnl;
	char	**cur_line;

	gnl = (t_gnl) {.fd = -1, .line = NULL, .ret = -1};
	data->world.size = (t_coord) {.x = 0, .y = 0};
	data->screen = (t_screen) {.floor_tex = 1, .ceil_tex = 1};
	if (checkformatfile(file, &gnl, ".cub"))
		return (EXIT_FAILURE);
	while (1)
	{
		gnl.ret = get_next_line(gnl.fd, &gnl.line);
		if (!gnl.line)
			return (ft_msg(TM_ERROR, "Line Null", 1, RED));
		if (data->world.map && ft_strcmp(gnl.line, "") == 0)
			return (ft_msg(TM_ERROR, "Blank in map", 1, RED));
		if ((!(cur_line = filter(data, gnl.line)))
		|| (cur_line[0] && parseparam(data, cur_line, gnl)))
			return (EXIT_FAILURE);
		wrfree(gnl.line);
		splitfree(cur_line);
		if (gnl.ret <= 0)
			break ;
	}
	close(gnl.fd);
	return (load_tex(data));
}
