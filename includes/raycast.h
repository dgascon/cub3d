/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   raycast.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <dgascon@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/13 11:52:37 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/11 15:22:52 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H
# include "cub3d.h"

typedef struct s_data	t_data;

typedef struct	s_raycast
{
	int			column;
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
int				fill_column(t_data *data);
float			linear_intersec_h(t_data *data);
float			linear_intersec_v(t_data *data);
#endif
