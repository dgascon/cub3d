/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 18:41:01 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/11 13:17:37 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int		parse_player(t_data *data, char direction, t_coord position)
{
	if (data->player.pos.x != 0 && data->player.pos.y != 0)
	{
		ft_printf("Deux joueurs de placé sur la carte !\n");
		freemap(data, 0);
		free(data->world.map);
		return (-1);
	}
	if (direction == 'N')
		data->player.pov = POV_NORTH;
	else if (direction == 'E')
		data->player.pov = POV_EAST;
	else if (direction == 'S')
		data->player.pov = POV_SOUTH;
	else if (direction == 'W')
		data->player.pov = POV_WEST;
	data->player.pos.x = (BLOCK_SIZE * position.x) + 32;
	data->player.pos.y = (BLOCK_SIZE * position.y) - 32;
	return (1);
}

char	**parse_map(t_data *data, char *line)
{
	char		**tmp_map;
	int			i;
	
	i = 0;
	if (!line)
		return (NULL);
	data->world.size.y++;
	if (!(tmp_map = malloc(sizeof(char *) * (data->world.size.y))))
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
	free(data->world.map);
	data->world.map = tmp_map;
   	if (data->world.size.x == 0)
		data->world.size.x = ft_strlen(tmp_map[i]);
	else if (data->world.size.x != (int)ft_strlen(tmp_map[i]))
	{
		ft_printf("Erreur de map\n");
		freemap(data, 1);
		free(data->world.map);
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
		else if(line[i] > '1')
		{
			lsprite_addback(&data->lst, lsprite_new((t_coord){.x = i, .y = data->world.size.y - 1}, data->object[line[i] - 50]));
		}
		i++;
	}
	return (data->world.map);
}

static int	init_object(t_data *data, char *path, int id)
{
	t_image *current_tex;

	current_tex = &data->object[id - 2];
	if (!(current_tex->img = mlx_xpm_file_to_image(data->mlx.ptr, path, &current_tex->sizex, &current_tex->sizey)))
		return (EXIT_FAILURE);
	if (!(current_tex->add_image = mlx_get_data_addr(current_tex->img, &current_tex->bpp, &current_tex->size_line, &current_tex->endian)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
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
            if (data->screen.size.x == 0
            && data->screen.size.y == 0)
		    {
			    data->screen.size.x = ft_atoi(&gnl.line[1]);
			    data->screen.size.y = ft_atoi(&gnl.line[ft_digit(data->screen.size.x) + 2]);
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
			indexparam = ft_atoi(&gnl.line[1]);
			if (ft_isdigit(gnl.line[1]))
			{
				if (indexparam > 1)
				{
					if (init_object(data, ft_delcharstr(&gnl.line[3], " "), indexparam))
						return (-1);
				}
			}
		}
        else if (ft_isdigit(gnl.line[0]))
        {
    		if (!(parse_map(data, ft_delcharstr(gnl.line, " "))))
				return (-1);

        }
		free(gnl.line);
		if (gnl.ret <= 0)
			break ;
	}
	close(gnl.fd);
	if (data->player.pos.x == 0 && data->player.pos.y == 0)
	{
		ft_printf("Aucun joueur sur la carte\n");
		freemap(data, 0);
		free(data->world.map);
		return (-1);
	}
	
	return (1);
}


// int parsefile(t_data *data, char *file)
// {
//     int fd;
//     char *line;
//     int i;
//     char **map;
//     int never_do = 1;
//     int ret;

//     i = 1;
//     int o = 0;
//     line = NULL;
//     printf("file =%s\n", file);
//     fd = open(file, O_RDONLY);
//     if (fd <= 0)
//     {
//         printf("open error\n");
//         return (0);
//     }
//     map = malloc(10 * sizeof(char *));
//     ret = 1;
//     while (ret > 0)
//     {
//         ret = get_next_line(fd, &line);
//         i = 1;
//         if (!line)
//         {
//             printf("GNL error\n");
//             return(-1);
//         }
//         printf("|%s|\n", line);
//         if (line[0]  == 'R')
//         {
//             data->screen.size.x = ft_atoi(&line[i]);
//             while (!(line[i] >= '0' && line[i] <= '9'))
//                 i++;
//             while (line[i] >= '0' && line[i] <= '9')
//             {
//                 i++;
//             }
//             data->screen.size.y = ft_atoi(&line[i]);
//             free(line);
//         }
//         else
//         {
//             if (never_do == 1)
//             {
//                 data->world.size.x = ft_strlen(line);
//                 never_do = 0;
//             }
//             map[o] = line;
//             o++;
// //	 free(line);

// 	}
// 	map[o] = NULL;
//     }
//     data->world.size.y = o;
//     printf("map y =%d, mapx = %d", data->world.size.y, data->world.size.x);
//     close(fd);
//     return (1);
// }
