/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 18:41:01 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/13 12:01:31 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

static int	checkformatfile(char *file, t_gnl *gnl)
{
	if (ft_strcmp(file + ft_strlen(file) - 4, ".cub") != 0)
		return (ft_message(TM_ERROR, "Extention de la map, non correct.",
				EXIT_FAILURE, RED));
	if (((*gnl).fd = open(file, O_RDONLY)) <= 0)
		return (ft_message(TM_ERROR, "Ouverture du fichier impossible.",
				EXIT_FAILURE, RED));
	return (EXIT_SUCCESS);
}

char	**filter(char *line)
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

static int flaginit_tex(t_data *data, int flag, t_image *img, char *path)
{
	if (flag)
		return (init_texture(data, img, path));
	return (EXIT_SUCCESS);
}

int	parse_set_resolu(t_data *data, char **line)
{
	if (!ft_strcmp(line[0], "R"))
	{
		if (data->screen.size.x == 0 && data->screen.size.y == 0)
		{
			if (!line[2])
				return (ft_message(TM_ERROR, "Resolution x, y manquante.",
					1, RED));
			data->screen.size.x = ft_atoi(&line[1]);
			data->screen.size.y = ft_atoi(&line[2]);
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
	if (flaginit_tex(data, !ft_strcmp(line[0], "F"),
		&data->w_tex[4], line[1]))
			return (EXIT_FAILURE);
	else if (flaginit_tex(data, !ft_strcmp(line[0], "C"),
		&data->w_tex[5], line[1]))
			return (EXIT_FAILURE);
	else if (flaginit_tex(data, !ft_strcmp(line[0], "NO"),
	 	&data->w_tex[0], line[1]))
			return (EXIT_FAILURE);
	else if (flaginit_tex(data, !ft_strcmp(line[0], "WE"),
	 	&data->w_tex[3], line[1]))
			return (EXIT_FAILURE);
	else if (flaginit_tex(data, !ft_strcmp(line[0], "EA"),
	 	&data->w_tex[1], line[1]))
			return (EXIT_FAILURE);
	else if (flaginit_tex(data, !ft_strcmp(line[0], "V"),
		&data->hud_tex[0], line[1]))
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

int	parsefile(t_data *data, char *file)
{
	t_gnl	gnl;
	t_coord	grid;
	char	**cur_line;

	grid = (t_coord) {};
	data->world = (t_world) {};
	gnl = (t_gnl) {};
	checkformatfile(file, &gnl);
	while (1)
	{
		gnl.ret = get_next_line(gnl.fd, &gnl.line);
		cur_line = filter(gnl.line);
		if (cur_line[0])
		{
			if (parse_set_resolu(data, cur_line))
				return (EXIT_FAILURE);
			else if (data->screen.size.x == 0 && data->screen.size.y == 0)
				return (ft_message(TM_ERROR, "La resolution n'est pas definie.",
							1, RED));
			else if (parse_set_object(data, cur_line))
				return (EXIT_FAILURE);
			else if (parse_set_tex(data, cur_line, gnl))
				return (EXIT_FAILURE);
		}
		wrfree(gnl.line);
		splitfree(cur_line);
		if (gnl.ret <= 0)
			break ;
	}
	close(gnl.fd);
	if (data->player.pos.x == 0 && data->player.pos.y == 0)
		return (ft_message(TM_ERROR, "Aucun joueur sur la map.", 1, RED));
	return (EXIT_SUCCESS);
}
