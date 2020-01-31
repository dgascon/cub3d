/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 18:41:01 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 06:09:40 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

char **parse_map(t_data *data, char *line)
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
	return (data->world.map);
}

int	parsefile(t_data *data, char *file)
{
	t_gnl	gnl;
	t_coord	grid;

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
		    }
            else
            {
                ft_printf("Argument doublé");
                return (-1);
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
	// show_map(data);
	close(gnl.fd);
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
