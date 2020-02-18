/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceil.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecaill <nlecaill@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 17:58:25 by dgascon           #+#    #+#             */
/*   Updated: 2020/02/18 15:18:49 by nlecaill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_background(t_data *data)
{
	int i;

	i = 0;
	while (i < data->player.hdv && i < data->screen.size.y)
	{
		*(int*)(data->image.add_image + (i * data->image.size_line) + (data->raycast.column * sizeof(int))) =
		rgb_int(data->screen.sky_color[0], data->screen.sky_color[1], data->screen.sky_color[2]);
		i++;
	}
	while (i < data->screen.size.y)
	{
		*(int*)(data->image.add_image + (i * data->image.size_line) + (data->raycast.column * sizeof(int))) =
		rgb_int(data->screen.floor_color[0], data->screen.floor_color[1], data->screen.floor_color[2]);
		i++;
	}
}

void	floor_ceil_v(t_data *data, t_floor *floor, t_floor *ceil)
{
	t_f_coord	sincos;

	sincos.x = 0;
	sincos.y = 0;
	if (data->raycast.alpha > M_PI_2 && data->raycast.alpha < _3PI2)
	{
		data->raycast.gamma = M_PI - data->raycast.alpha ;
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

void	floor_ceil_h(t_data *data, t_floor *floor, t_floor *ceil)
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

int		floor_ceil_color(t_data *data, float c_const[4], int qte_mur_sur_hdv, int *val2)
{
	t_floor		floor;
	t_floor		ceil;
	t_f_coord	sincos;

	ceil.dist = c_const[0] - (c_const[2] / qte_mur_sur_hdv);
	floor.dist = c_const[0] - (c_const[3] / c_const[1]);
	(floor.dist < 1) ? floor.dist = 1 : 0;
	if (ceil.dist < 1)
		ceil.dist = 1;
	sincos.x = 0;
	sincos.y = 0;
	if (data->raycast.face_detect == 'H')
		floor_ceil_h(data, &floor, &ceil);
	else
		floor_ceil_v(data, &floor, &ceil);
	floor.pos.x = (int)(((float)data->w_tex[4].size.x / BLOCK_SIZE) * (data->raycast.inter.x + floor.delta.x)) % (data->w_tex[4].size.x);
	floor.pos.y = (int)(((float)data->w_tex[4].size.y / BLOCK_SIZE) * (data->raycast.inter.y + floor.delta.y)) % (data->w_tex[4].size.y);
	ceil.pos.x = (int)(((float)data->w_tex[5].size.x / BLOCK_SIZE) * (data->raycast.inter.x + ceil.delta.x)) % (data->w_tex[5].size.x);
	ceil.pos.y = (int)(((float)data->w_tex[5].size.y / BLOCK_SIZE) * (data->raycast.inter.y + ceil.delta.y)) % (data->w_tex[5].size.y);
	*val2 = *(int*)(data->w_tex[5].add_image + (data->w_tex[5].size_line * ceil.pos.y) + (ceil.pos.x * sizeof(int)));
	return (*(int*)(data->w_tex[4].add_image + (data->w_tex[4].size_line * floor.pos.y) + (floor.pos.x * sizeof(int))));
}

void	print_only_ceil(t_data *data, float val_cst[4], int qte_mur_sur_hdv)
{
	int		val2;
	char	*add_opp;
	int		crow;
	
	crow = data->screen.size.y - 1;
	add_opp = data->image.add_image + (data->raycast.column * sizeof(int));
	while (crow >= 0)
	{
		floor_ceil_color(data, val_cst, qte_mur_sur_hdv, &val2);
		*(int*)(add_opp + (data->image.size_line * (crow))) = val2;
		crow--;
		val_cst[1]++;
		qte_mur_sur_hdv++;
	}
}

void	pt_floor_ceil(t_data *data, int row, int qte_mur_sous_hdv, int height_proj_plane, int h_max)
{
	float   cosB;
	float   val_cst[4];
	int		val2;
	int     val1;
	int     crow;
	int     qte_mur_sur_hdv;
	char    *add_opp;
	
	add_opp = data->image.add_image + (data->raycast.column * sizeof(int));
	qte_mur_sur_hdv = height_proj_plane - qte_mur_sous_hdv;
	if (qte_mur_sur_hdv < 1)
		qte_mur_sur_hdv = 1;
	crow = (data->player.hdv - qte_mur_sur_hdv);
	cosB = cosf(data->raycast.beta);
	val_cst[0] = (data->raycast.dist / cosB);
	val_cst[1] = qte_mur_sous_hdv;
	val_cst[2] = (data->player.dist_proj_plane / cosB) * (BLOCK_SIZE - data->player.height_cam);
	val_cst[3] = (data->player.dist_proj_plane / cosB) * (data->player.height_cam);
	row = h_max;
	//TODO faire du cas par cas avec ceil only, floor only
	if (data->player.hdv < data->screen.size.y / 2)
	{
		// quand il y a plus de de sol que de plafond
		if (row < 0) //permet d'avoir 1 condition par colonne plutot que par pixel
		{
			qte_mur_sur_hdv -= row;
			val_cst[1] -= row;
			row = 0;
			crow = -1;
		}
		while (row < data->screen.size.y)
		{
			*(int*)(add_opp + (row * data->image.size_line)) = floor_ceil_color(data, val_cst, qte_mur_sur_hdv, &val2);
			if (crow >= 0)
			{
				*(int*)(add_opp + (data->image.size_line * (crow))) = val2;
				crow--;
			}
			row++;
			val_cst[1]++;
			qte_mur_sur_hdv++;
		}
	}
	else
	{
		if (crow > data->screen.size.y - 1)
		{
			qte_mur_sur_hdv += crow - (data->screen.size.y - 1);
			val_cst[1] += crow - (data->screen.size.y - 1);
			crow = data->screen.size.y - 1;
			print_only_ceil(data, val_cst, qte_mur_sur_hdv);
			return ;
		}
		while (crow >= 0)
		{
			val1 = floor_ceil_color(data, val_cst, qte_mur_sur_hdv, &val2);
			*(int*)(add_opp + (data->image.size_line * (crow))) = val2;
			if (row < data->screen.size.y)
			{
				*(int*)(add_opp + (row * data->image.size_line)) = val1;
				row++;
			}
			crow--;
			val_cst[1]++;
			qte_mur_sur_hdv++;
		}
	}
}
