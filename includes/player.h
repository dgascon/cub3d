/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebastienlecaille <sebastienlecaille@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:27:41 by dgascon           #+#    #+#             */
/*   Updated: 2022/02/11 16:22:52 by sebastienle      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include "cub3d.h"
# include "raycast.h"

# define MAX_SPEED 15

typedef struct		s_player
{
	float			fov;
	float			pov;
	int				height_cam;
	t_f_coord		pos;
	int				speed;
	float			dist_proj_plane;
	int				cst;
	int				hdv;
	enum e_boolean	show_minimap;
}					t_player;

typedef	struct		s_actions
{
	enum e_boolean	forward;
	enum e_boolean	backward;
	enum e_boolean	leftward;
	enum e_boolean	rightward;
	enum e_boolean	lookleft;
	enum e_boolean	lookright;
	enum e_boolean	lookup;
	enum e_boolean	lookdown;
	enum e_boolean	speed;
	enum e_boolean	crouching;
	enum e_boolean	jump;
}					t_actions;

int					key_press(int key, t_data *data);
int					key_release(int key, t_data *data);
void				actionscontrol(t_data *data);
void				move(t_data *data, float direction);
#endif
