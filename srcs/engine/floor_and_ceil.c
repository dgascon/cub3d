/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceil.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecaill <nlecaill@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 17:58:25 by dgascon           #+#    #+#             */
/*   Updated: 2020/02/28 16:13:26 by nlecaill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		fill_background(t_data *data)
{
	int i;

	i = 0;
	while (i < data->player.hdv && i < data->screen.size.y - 1)
	{
		*(int*)(data->image.add_image + (i * data->image.size_line)
		+ (data->raycast.column * sizeof(int))) =
		rgb_int(0, data->screen.sky_color[0],
		data->screen.sky_color[1], data->screen.sky_color[2]);
		i++;
	}
	while (i < data->screen.size.y - 1)
	{
		*(int*)(data->image.add_image
		+ (i * data->image.size_line) + (data->raycast.column * sizeof(int))) =
		rgb_int(0, data->screen.floor_color[0],
		data->screen.floor_color[1], data->screen.floor_color[2]);
		i++;
	}
}

static void	print_only_ceil(t_data *data, float val_cst[4], int qte_mur_sur_hdv)
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
/*
static void	more_floor(t_data *data, float clc_cst[4], int wall_up_hdv, int row)
{
	char	*add_opp;
	int		val2;
	int		crow;

	add_opp = data->image.add_image + (data->raycast.column * sizeof(int));
	crow = (data->player.hdv - wall_up_hdv);
	if (row < 0)
	{
		wall_up_hdv -= row;
		clc_cst[1] -= row;
		row = 0;
		crow = -1;
	}
	while (row < data->screen.size.y)
	{
		*(int*)(add_opp + (row * data->image.size_line)) =
		floor_ceil_color(data, clc_cst, wall_up_hdv, &val2);
		if (crow >= 0)
			*(int*)(add_opp + (data->image.size_line * (crow--))) = val2;
		row++;
		clc_cst[1]++;
		wall_up_hdv++;
	}
}
*/
static void	more_ceil(t_data *data, float calc_cst[4], int wall_up_hdv, int row)
{
	char	*add_opp;
	int		val2;
	int		val1;
	int		crow;

	crow = (data->player.hdv - wall_up_hdv);
	add_opp = data->image.add_image + (data->raycast.column * sizeof(int));
	if (crow > data->screen.size.y - 1)
	{
		wall_up_hdv += crow - (data->screen.size.y - 1);
		calc_cst[1] += crow - (data->screen.size.y - 1);
		crow = data->screen.size.y - 1;
		print_only_ceil(data, calc_cst, wall_up_hdv);
		return ;
	}
	if (crow >= data->screen.size.y - 1)
		crow = data->screen.size.y - 1;

	while (crow >= 0 || row < data->screen.size.y - 1)
	{
		val1 = floor_ceil_color(data, calc_cst, wall_up_hdv, &val2);
		if (crow >= 0)
		{
			*(int*)(add_opp + (data->image.size_line * crow--)) = val2;
		}
		if (row < data->screen.size.y - 1 && row >= 0)
		{
			*(int*)(add_opp + (row * data->image.size_line)) = val1;
		}
		row++;
		calc_cst[1]++;
		wall_up_hdv++;
	}
}

void		pt_floor_ceil(t_data *data, int row, int qte_mur_sous_hdv,
						int height_proj_plane)
{
	float	cosb;
	float	calc_cst[4];
	int		crow;
	int		qte_mur_sur_hdv;

	qte_mur_sur_hdv = height_proj_plane - qte_mur_sous_hdv;
	if (qte_mur_sur_hdv < 1)
		qte_mur_sur_hdv = 1;
	crow = (data->player.hdv - qte_mur_sur_hdv);
	cosb = cosf(data->raycast.beta);
	calc_cst[0] = (data->raycast.dist / cosb);
	calc_cst[1] = qte_mur_sous_hdv;
	calc_cst[2] = (data->player.dist_proj_plane / cosb)
		* (BLOCK_SIZE - data->player.height_cam);
	calc_cst[3] = (data->player.dist_proj_plane / cosb)
		* (data->player.height_cam);
		more_ceil(data, calc_cst, qte_mur_sur_hdv, row);
}
