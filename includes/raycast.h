/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <dgascon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 16:51:58 by dgascon           #+#    #+#             */
/*   Updated: 2020/05/01 10:21:23 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H
# include "cub3d.h"

typedef struct s_data	t_data;

typedef struct	s_raycast
{
	int			column;
	int			end;
	float		alpha;
	float		beta;
	float		gamma;
	float		dist;
	float		dist_h;
	char		face_detect;
	t_f_coord	inter;
	t_f_coord	inter_h;
	float		delta_ang;
}				t_raycast;

float			short_dist(t_data *data);
int				fill_column(t_data *data, int direction);
void			print_sprite(t_data *data);
float			linear_intersec_h(t_data *data);
float			linear_intersec_v(t_data *data);
void			fill_background(t_data *data);
float			browse_h(t_data *data, t_f_coord intersec, t_f_coord offset);
float			browse_v(t_data *data, t_f_coord intersec, t_f_coord offset);

#endif
