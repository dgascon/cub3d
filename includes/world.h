/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   world.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 17:30:10 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/15 12:26:09 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H
# include "cube3d.h"

typedef struct	s_world
{
	int			width;
	int			height;
	char		data[320][200];
	t_player 	player;
}				t_world;

void	*init_world(t_world *world);
void	*show_2d_world(t_world *world);
double	shortest_dist(double horizontal, double vertical);
void    put_column(int column, t_data *win, t_raycast *raycast);
#endif