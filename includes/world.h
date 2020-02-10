/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   world.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nlecaill <nlecaill@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 17:30:10 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/10 15:00:42 by nlecaill    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H
# include "cub3d.h"

# define BLOCK_SIZE 64

typedef struct s_data t_data;

typedef struct	s_world
{
	char		**map;
	t_coord		size;
}				t_world;

int				parsefile(t_data *data, char *file);
void			freemap(t_data *data, int offset);

#endif