/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   world.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nlecaill <nlecaill@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 17:30:10 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/12 15:19:52 by nlecaill    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H
# include "cub3d.h"

# define BLOCK_SIZE 128

typedef struct s_data	t_data;

typedef struct	s_world
{
	char		**map;
	t_coord		size;
	int			locked;
	int			was_lock;
}				t_world;

int				parsefile(t_data *data, char *file);
void			freemap(t_data *data, int offset);
int				parse_player(t_data *data, char direction, t_coord position);
#endif
