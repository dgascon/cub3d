/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 18:41:01 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/12 19:00:59 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

char	**parse_map(t_data *data, char *line)
{
	char		**tmp_map;
	int			i;
	
	i = 0;
	if (!line)
		return (NULL);
	data->world.size.y++;
	if (!(tmp_map = wrmalloc(sizeof(char *) * (data->world.size.y))))
	{
		ft_printf("Malloc en y impossible.\n");
		return (NULL);
	}
	while (i < data->world.size.y - 1)
	{
		if (!(tmp_map[i] = ft_substr(data->world.map[i], 0,
								ft_strlen(data->world.map[i]))))
			return (NULL);
		i++;
	}
	tmp_map[i] = line;
	(data->world.size.y > 1) ? freemap(data, 1) : 0;
	wrfree(data->world.map);
	data->world.map = tmp_map;
   	if (data->world.size.x == 0)
		data->world.size.x = ft_strlen(tmp_map[i]);
	else if (data->world.size.x != (int)ft_strlen(tmp_map[i]))
	{
		ft_printf("Erreur de map\n");
		freemap(data, 1);
		wrfree(data->world.map);
		return (NULL);
	}
	i = 0;
	while (line[i])
	{
		if (ft_charstr(line[i], "NSWE"))
		{
			if (parse_player(data, line[i],
				(t_coord) {.x = i, .y = data->world.size.y}) <= 0)
				return (NULL);
		}
		else if(line[i] > '2')
		{
			lsprite_addback(&data->lst, lsprite_new((t_coord){.x = i, .y = data->world.size.y - 1}, data->object[line[i] - 51]));
		}
		i++;
	}
	return (data->world.map);
}

int	parsefile(t_data *data, char *file)
{
	t_gnl	gnl;
	t_coord	grid;
	int		indexparam;

	grid = (t_coord) {};
	data->world = (t_world) {};
	if (ft_strcmp(file + ft_strlen(file) - 4, ".cub") != 0)
	{
		ft_printf("Extention de la map, non correct '%s'!\n", file);
		return (-1);
	}
	if ((gnl.fd = open(file, O_RDONLY)) <= 0)
	{
		ft_printf("Probleme a l'ouverture du fichier '%s'!\n", file);
		return (-1);
	}
	while (1)
	{
		gnl.ret = get_next_line(gnl.fd, &gnl.line);
		if (gnl.line[0] == 'R')
        {
            if (data->screen.size.x == 0 && data->screen.size.y == 0)
		    {
			    data->screen.size.x = ft_atoi(&gnl.line[1]);
			    data->screen.size.y = ft_atoi(&gnl.line[ft_digit(data->screen.size.x) + 2]);
				(data->screen.size.x >= 2560) ? data->screen.size.x = 2559 : 0;
				(data->screen.size.y >= 1440) ? data->screen.size.y = 1439 : 0;
				init_window(data);
		    }
            else
            {
                ft_printf("Argument doublé");
                return (-1);
            }
        }
		else if (gnl.line[0] == 'S')
		{
			if (ft_isdigit(gnl.line[1]))
			{
				if ((indexparam = ft_atoi(&gnl.line[1])) > 2)
				{
					if (init_texture(data, &data->object[indexparam - 3],
						ft_delcharstr(&gnl.line[3], " ")))
						return (-1);
				}
			}
			else if (gnl.line[1] == 'O')
				init_texture(data, &data->w_tex[2], ft_delcharstr(&gnl.line[3], " ")); //TODO PROTEGER
		}
		else if (gnl.line[0] == 'F')
			init_texture(data, &data->w_tex[4], ft_delcharstr(&gnl.line[2], " ")); //TODO PROTEGER
		else if (gnl.line[0] == 'C')
			init_texture(data, &data->w_tex[5], ft_delcharstr(&gnl.line[2], " ")); //TODO PROTEGER
		else if (gnl.line[0] == 'N' && gnl.line[1] == 'O')
			init_texture(data, &data->w_tex[0], ft_delcharstr(&gnl.line[3], " ")); //TODO PROTEGER
		else if (gnl.line[0] == 'W' && gnl.line[1] == 'E')
			init_texture(data, &data->w_tex[3], ft_delcharstr(&gnl.line[3], " ")); //TODO PROTEGER
		else if (gnl.line[0] == 'E' && gnl.line[1] == 'A')
			init_texture(data, &data->w_tex[1], ft_delcharstr(&gnl.line[3], " ")); //TODO PROTEGER
		else if (gnl.line[0] == 'V')
			init_texture(data, &data->hud_tex[0], ft_delcharstr(&gnl.line[2], " ")); //TODO PROTEGER
        else if (ft_isdigit(gnl.line[0]))
        {
    		if (!(parse_map(data, ft_delcharstr(gnl.line, " "))))
				return (-1);
        }
		wrfree(gnl.line);
		if (gnl.ret <= 0)
			break ;
	}
	close(gnl.fd);
	if (data->player.pos.x == 0 && data->player.pos.y == 0)
	{
		ft_printf("Aucun joueur sur la carte\n");
		freemap(data, 0);
		wrfree(data->world.map);
		return (-1);
	}
	return (1);
}
