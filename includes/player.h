/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   player.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 17:27:41 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/13 11:36:29 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "cube3d.h"

typedef struct	s_player
{
	double	fov; //Field of view | Largeur de la vue
	int		height;
	double	pov; //Point of view | Angle de vue
	t_coord	coord;
}				t_player;

#endif