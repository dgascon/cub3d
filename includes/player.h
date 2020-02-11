/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   player.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/09 17:27:41 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/11 15:15:03 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include "cub3d.h"
# include "raycast.h"

# define MAX_SPEED 20

typedef struct s_data	t_data;

typedef struct		s_player
{
	float			fov;
	float			pov;
	int				height_cam;
	t_coord			pos;
	int				speed;
	float			dist_proj_plane;
	int				cst;
	int				hdv;
	enum e_boolean	show_minimap;
}					t_player;

int					key_press(int key, t_data *data);
int					key_release(int key, t_data *data);
int					destroy(t_data *data);
void				move(t_data *data, float direction);
#endif
