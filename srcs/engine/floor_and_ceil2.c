/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceil2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecaill <nlecaill@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 16:17:42 by nlecaill          #+#    #+#             */
/*   Updated: 2020/02/18 16:23:53 by nlecaill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	floor_ceil_v(t_data *data, t_floor *floor, t_floor *ceil)
{
	t_f_coord	sincos;

	sincos.x = 0;
	sincos.y = 0;
	if (data->raycast.alpha > M_PI_2 && data->raycast.alpha < _3PI2)
	{
		data->raycast.gamma = M_PI - data->raycast.alpha;
		__sincosf(data->raycast.gamma, &sincos.x, &sincos.y);
		floor->delta.x = floor->dist * sincos.y;
		ceil->delta.x = ceil->dist * sincos.y;
	}
	else
	{
		data->raycast.gamma = data->raycast.alpha - _2PI;
		__sincosf(data->raycast.gamma, &sincos.x, &sincos.y);
		floor->delta.x = floor->dist * sincos.y * -1;
		ceil->delta.x = ceil->dist * sincos.y * -1;
	}
	floor->delta.y = floor->dist * sincos.x;
	ceil->delta.y = ceil->dist * sincos.x;
}

static void	floor_ceil_h(t_data *data, t_floor *floor, t_floor *ceil)
{
	t_f_coord	sincos;

	sincos.x = 0;
	sincos.y = 0;
	if (data->raycast.alpha > 0 && data->raycast.alpha < M_PI)
	{
		data->raycast.gamma = data->raycast.alpha - (M_PI_2);
		__sincosf(data->raycast.gamma, &sincos.x, &sincos.y);
		floor->delta.y = floor->dist * sincos.y;
		ceil->delta.y = ceil->dist * sincos.y;
	}
	else
	{
		data->raycast.gamma = (_3PI2) - data->raycast.alpha;
		__sincosf(data->raycast.gamma, &sincos.x, &sincos.y);
		floor->delta.y = floor->dist * sincos.y * -1;
		ceil->delta.y = ceil->dist * sincos.y * -1;
	}
	floor->delta.x = floor->dist * sincos.x;
	ceil->delta.x = ceil->dist * sincos.x;
}

int			floor_ceil_color(t_data *data, float c_const[4], int qte_mur_sur_hdv
						, int *val2)
{
	t_floor		floor;
	t_floor		ceil;
	t_f_coord	sincos;

	ceil.dist = c_const[0] - (c_const[2] / qte_mur_sur_hdv);
	floor.dist = c_const[0] - (c_const[3] / c_const[1]);
	(floor.dist < 1) ? floor.dist = 1 : 0;
	(ceil.dist < 1) ? ceil.dist = 1 : 0;
	sincos = (t_f_coord){0.0, 0.0};
	if (data->raycast.face_detect == 'H')
		floor_ceil_h(data, &floor, &ceil);
	else
		floor_ceil_v(data, &floor, &ceil);
	floor.pos.x = (int)(((float)data->w_tex[4].size.x / BLOCK_SIZE)
		* (data->raycast.inter.x + floor.delta.x)) % (data->w_tex[4].size.x);
	floor.pos.y = (int)(((float)data->w_tex[4].size.y / BLOCK_SIZE)
		* (data->raycast.inter.y + floor.delta.y)) % (data->w_tex[4].size.y);
	ceil.pos.x = (int)(((float)data->w_tex[5].size.x / BLOCK_SIZE)
		* (data->raycast.inter.x + ceil.delta.x)) % (data->w_tex[5].size.x);
	ceil.pos.y = (int)(((float)data->w_tex[5].size.y / BLOCK_SIZE)
		* (data->raycast.inter.y + ceil.delta.y)) % (data->w_tex[5].size.y);
	*val2 = *(int*)(data->w_tex[5].add_image
		+ (data->w_tex[5].size_line * ceil.pos.y) + (ceil.pos.x * sizeof(int)));
	return (*(int*)(data->w_tex[4].add_image
	+ (data->w_tex[4].size_line * floor.pos.y) + (floor.pos.x * sizeof(int))));
}
