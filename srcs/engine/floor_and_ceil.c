/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceil.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecaill <nlecaill@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 17:58:25 by dgascon           #+#    #+#             */
/*   Updated: 2020/02/17 19:46:16 by nlecaill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void fill_background(t_data *data)
{
	int i;

	i = 0;
	while (i < data->player.hdv)
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

int floor_ceil_color(t_data *data, float c_const[4], float qte_mur_sur_hdv, int *val2)
{
	t_coord 	sol;
	t_coord 	ceil;
	float 		dist_mur_sol;
	float 		dist_mur_plafond;
	float 		deltaY[2];
	float 		deltaX[2];
	t_f_coord	sincos;

	// printf("IN\n");
	dist_mur_plafond = c_const[0] - (c_const[2] / qte_mur_sur_hdv);
	dist_mur_sol = c_const[0] - (c_const[3] / c_const[1]);
	sincos.x = 0;
	sincos.y = 0;
	if (data->raycast.face_detect == 'H')
	{
		if (data->raycast.alpha > 0 && data->raycast.alpha < M_PI)
		{
			data->raycast.gamma = data->raycast.alpha - (M_PI_2);
			__sincosf(data->raycast.gamma, &sincos.x, &sincos.y);
			deltaY[0] = dist_mur_sol * sincos.y;
			deltaY[1] = dist_mur_plafond * sincos.y;
		}
		else
		{
			data->raycast.gamma = (_3PI2) - data->raycast.alpha;
			__sincosf(data->raycast.gamma, &sincos.x, &sincos.y);
			deltaY[0] = dist_mur_sol * sincos.y * -1;
			deltaY[1] = dist_mur_plafond * sincos.y * -1;
		}
		deltaX[0] = dist_mur_sol * sincos.x;
		deltaX[1] = dist_mur_plafond * sincos.x;
	}
	else
	{
		if (data->raycast.alpha > M_PI_2 && data->raycast.alpha < _3PI2)
		{
			data->raycast.gamma = M_PI - data->raycast.alpha ;
			__sincosf(data->raycast.gamma, &sincos.x, &sincos.y);
			deltaX[0] = dist_mur_sol * sincos.y;
			deltaX[1] = dist_mur_plafond * sincos.y;
		}
		else
		{
			data->raycast.gamma = data->raycast.alpha - _2PI;
			__sincosf(data->raycast.gamma, &sincos.x, &sincos.y);
			deltaX[0] = dist_mur_sol * sincos.y * -1;
			deltaX[1] = dist_mur_plafond * sincos.y * -1;
		}
		deltaY[0] = dist_mur_sol * sincos.x;
		deltaY[1] = dist_mur_plafond * sincos.x;
	}
	sol.x = (int)(((float)data->w_tex[4].size.x / BLOCK_SIZE) * (data->raycast.inter.x + deltaX[0])) % (data->w_tex[4].size.x);
	sol.y = (int)(((float)data->w_tex[4].size.y / BLOCK_SIZE) * (data->raycast.inter.y + deltaY[0])) % (data->w_tex[4].size.y);
	ceil.x = (int)(((float)data->w_tex[5].size.x / BLOCK_SIZE) * (data->raycast.inter.x + deltaX[1])) % (data->w_tex[5].size.x);
	ceil.y = (int)(((float)data->w_tex[5].size.y / BLOCK_SIZE) * (data->raycast.inter.y + deltaY[1])) % (data->w_tex[5].size.y);
	// printf("challenge\n%f\n", dist_mur_plafond);// (data->raycast.inter.y + deltaY[1]));
	*val2 = *(int*)(data->w_tex[5].add_image + (data->w_tex[5].size_line * ceil.y) + (ceil.x * sizeof(int)));
	// printf("out\n");
	return (*(int*)(data->w_tex[4].add_image + (data->w_tex[4].size_line * sol.y) + (sol.x * sizeof(int))));
}

void	print_only_ceil(t_data *data, float val_cst[4], int qte_mur_sur_hdv)
{
	int val2;
	char *add_opp;
	int crow = data->screen.size.y - 1;

	// printf("only\n");
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

void    pt_floor_ceil(t_data *data, int row, float qte_mur_sous_hdv, float height_proj_plane, int h_max)
{
	float   cosB;
	float   val_cst[4];
	int		val2;
	int     val1;
	int     crow;
	float     qte_mur_sur_hdv;
	char    *add_opp;
	
	// printf("come in floor&&ceil\n");
	add_opp = data->image.add_image + (data->raycast.column * sizeof(int));
	qte_mur_sur_hdv = height_proj_plane - qte_mur_sous_hdv;
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
		// printf("heeeey\n");
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
	// printf("out\n");
}
