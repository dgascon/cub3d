/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   player.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 17:27:41 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/04 19:43:18 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include "cub3d.h"
# include "raycast.h"

# define POV_NORTH M_PI / 2
# define POV_EAST 2 * M_PI
# define POV_SOUTH 3 * M_PI_2
# define POV_WEST M_PI

typedef struct s_data t_data;

typedef struct	s_player
{
	float	fov; //ANCHOR Field of view | Largeur de la vue
	float	pov; //ANCHOR Point of view | Angle de vue
	int		height_cam;
	t_coord	pos;
	int		speed;
	float dist_proj_plane;
	int		CST;
	int		hdv;
	enum e_boolean show_minimap;
}				t_player;

int				key_press(int key, t_data *data);
int				key_release(int key, t_data *data);
void			destroy(t_data *data);

#endif