/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   player.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 17:27:41 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 05:23:34 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include "cub3d.h"
# include "raycast.h"

typedef struct s_data t_data;

typedef struct	s_player
{
	double	fov; //ANCHOR Field of view | Largeur de la vue
	double	pov; //ANCHOR Point of view | Angle de vue
	int		height_cam;
	t_coord	pos;
	int		speed;
	double dist_proj_plane;
	int		CST;
	int		hdv;
}				t_player;

int				key_press(int key, t_data *data);
int				key_release(int key, t_data *data);

#endif