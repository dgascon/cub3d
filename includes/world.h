/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecaill <nlecaill@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:30:10 by dgascon           #+#    #+#             */
/*   Updated: 2020/03/13 10:46:04 by nlecaill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H
# include "cub3d.h"

# define BLOCK_SIZE 64

typedef struct s_data	t_data;

typedef struct	s_world
{
	char		**map;
	int			*leny;
	t_coord		size;
}				t_world;

int				parse_floor_ceil(t_data *data, char **line);
int				parse_set_object(t_data *data, char **line);
int				parse_set_tex(t_data *data, char **line);
int				parse_set_resolu(t_data *data, char **line);
int				parsefile(t_data *data, char *file);
int				parse_player(t_data *data, char direction, t_coord position);
int				parse_map(t_data *data, char *line);
int				checkmapwall(t_data *data);
#endif
