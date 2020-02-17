/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceil.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecaill <nlecaill@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 17:58:25 by dgascon           #+#    #+#             */
/*   Updated: 2020/02/17 11:49:02 by nlecaill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void fill_background(t_data *data)
{
	int i;

	i = 0;
	while (i < data->screen.size.y / 2)
	{
		*(data->image.add_image + (i * data->image.size_line) + (data->raycast.column * sizeof(int))) = rgb_int(data->screen.sky_color[0], data->screen.sky_color[1], data->screen.sky_color[2]);
		i++;
	}
	while (i < data->screen.size.y)
	{
		*(data->image.add_image + (i * data->image.size_line) + (data->raycast.column * sizeof(int))) = rgb_int(data->screen.floor_color[0], data->screen.floor_color[1], data->screen.floor_color[2]);
		i++;
	}
}

int floor_ceil_color(t_data *data, float c_const[4], int hproj_plane, int *val2)
{
	t_coord 	sol;
	t_coord 	ceil;
	float 		dist_mur_sol;
	float 		dist_mur_plafond;
	float 		deltaY[2];
	float 		deltaX[2];
	t_f_coord	sincos;

	dist_mur_plafond = c_const[0] - (c_const[2] / hproj_plane);
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
	sol.x = (int)(((float)data->w_tex[4].size.x / BLOCK_SIZE) * (data->raycast.inter.x + deltaX[0])) % data->w_tex[4].size.x;
	sol.y = (int)(((float)data->w_tex[4].size.y / BLOCK_SIZE) * (data->raycast.inter.y + deltaY[0])) % data->w_tex[4].size.y;
	ceil.x = (int)(((float)data->w_tex[5].size.x / BLOCK_SIZE) * (data->raycast.inter.x + deltaX[1])) % data->w_tex[5].size.x;
	ceil.y = (int)(((float)data->w_tex[5].size.y / BLOCK_SIZE) * (data->raycast.inter.y + deltaY[1])) % data->w_tex[5].size.y;
	*val2 = *(int*)(data->w_tex[5].add_image + (data->w_tex[5].size_line * ceil.y) + (ceil.x * sizeof(int)));
	return (*(int*)(data->w_tex[4].add_image + (data->w_tex[4].size_line * sol.y) + (sol.x * sizeof(int))));
}

void	print_only_ceil(t_data *data, float val_cst[4], int toto)
{
	int val2;
	char *add_opp;
	int crow = 0;

	add_opp = data->image.add_image + (data->raycast.column * sizeof(int));
	while (crow < data->screen.size.y)
	{
		floor_ceil_color(data, val_cst, toto, &val2);
		*(int*)(add_opp + (data->image.size_line * (data->screen.size.y - crow))) = val2;
		crow++;
		val_cst[1]++;
		toto++;
	}
}

void    pt_floor_ceil(t_data *data, int row, int	gnagna, int height_proj_plane, int h_max)
{
	float   cosB;
	float   val_cst[4];
	int		val2;
	int     val1;
	int     crow;
	int     toto;
	char    *add_opp;
	
	add_opp = data->image.add_image + (data->raycast.column * sizeof(int));
	toto = height_proj_plane - gnagna;
	row = data->player.hdv - toto;
	crow = data->screen.size.y - row;
	cosB = cosf(data->raycast.beta);
	val_cst[0] = (data->raycast.dist / cosB);
	val_cst[1] = gnagna;
	val_cst[2] = (data->player.dist_proj_plane / cosB) * (BLOCK_SIZE - data->player.height_cam);
	val_cst[3] = (data->player.dist_proj_plane / cosB) * (data->player.height_cam);
	row = h_max;
	//TODO faire du cas par cas avec ceil only, floor only
	if (row < crow)
	{
		// quand il y a plus de de sol que de plafond
		if (row < 0) //permet d'avoir 1 condition par colonne plutot que par pixel
		{
			toto -= row;
			val_cst[1] -= row;
			row = 0;
			crow = data->screen.size.y + 1;
		}
		while (row < data->screen.size.y)
		{
			*(int*)(add_opp + (row * data->image.size_line)) = floor_ceil_color(data, val_cst, toto, &val2);
			if (crow <= data->screen.size.y)
			{
				*(int*)(add_opp + (data->image.size_line * (data->screen.size.y - crow))) = val2;
				crow++;
			}
			row++;
			val_cst[1]++;
			toto++;
		}
	}
	else
	{
		if (crow < 0)
		{
			toto -= crow;
			val_cst[1] -= crow;
			print_only_ceil(data, val_cst, toto);
			return ;
		}
		while (crow < data->screen.size.y)
		{
			val1 = floor_ceil_color(data, val_cst, toto, &val2);
			*(int*)(add_opp + (data->image.size_line * (data->screen.size.y - crow))) = val2;
			if (row <= data->screen.size.y)
			{
				*(int*)(add_opp + (row * data->image.size_line)) = val1;
				row++;
			}
			crow++;
			val_cst[1]++;
			toto++;
		}
	}
}
