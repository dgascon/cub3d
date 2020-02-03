/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   render.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dgascon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 17:58:25 by dgascon      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/23 17:19:41 by dgascon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int	select_sprite_color(t_data *data, int height_proj_plane, int wall_row)
{
	t_d_coord ratio;
	
	ratio.y = (int)(((double)data->Wtex.size / (double)height_proj_plane) * wall_row) % 64;
	ratio.x = (data->raycast.face_detect == 'V') ? ((int)(data->raycast.inter.y) % 64) : ((int)(data->raycast.inter.x) % 64);
	return (*(int*)(data->Wtex.add_image + (data->Wtex.size_line * (int)(ratio.y)) + ((int)ratio.x * sizeof(int))));
}

int floor_color(t_data *data, double calc_const[2], int height_proj_plane, int *val2)
{
	t_coord sol;
	t_coord ceil;
	float dist_mur_sol;
	float dist_mur_plafond;
	float deltaY[2];
	float deltaX[2];

	dist_mur_plafond = calc_const[0] - (calc_const[2] / height_proj_plane);
	dist_mur_sol = calc_const[0] - (calc_const[3] / calc_const[1]);

	if (data->raycast.face_detect == 'H')
	{
		if (data->raycast.alpha > 0 && data->raycast.alpha < M_PI)
		{
			data->raycast.gamma = data->raycast.alpha - (M_PI_2);
			deltaY[0] = dist_mur_sol * cos(data->raycast.gamma);
			deltaY[1] = dist_mur_plafond * cos(data->raycast.gamma);
		}
		else
		{
			data->raycast.gamma = (data->pi.tPId) - data->raycast.alpha;
			deltaY[0] = dist_mur_sol * cos(data->raycast.gamma) * -1;
			deltaY[1] = dist_mur_plafond * cos(data->raycast.gamma) * -1;
		}
		deltaX[0] = dist_mur_sol * sin(data->raycast.gamma);
		deltaX[1] = dist_mur_plafond * sin(data->raycast.gamma);
	}
	else
	{
		if (data->raycast.alpha > M_PI_2 && data->raycast.alpha < data->pi.tPId)
		{

			data->raycast.gamma = M_PI - data->raycast.alpha ;
			deltaX[0] = dist_mur_sol * cos(data->raycast.gamma);
			deltaX[1] = dist_mur_plafond * cos(data->raycast.gamma);
		}
		else
		{
			data->raycast.gamma = data->raycast.alpha - data->pi.dPI;
			deltaX[0] = dist_mur_sol * cos(data->raycast.gamma) * -1;
			deltaX[1] = dist_mur_plafond * cos(data->raycast.gamma) * -1;
		}
		deltaY[0] = dist_mur_sol * sin(data->raycast.gamma);
		deltaY[1] = dist_mur_plafond * sin(data->raycast.gamma);
	}
	sol.x = (int)(data->raycast.inter.x + deltaX[0]) % 64;
	sol.y = (int)(data->raycast.inter.y + deltaY[0]) % 64;
	ceil.x = (int)(data->raycast.inter.x + deltaX[1]) % 64;
	ceil.y = (int)(data->raycast.inter.y + deltaY[1]) % 64;
	*val2 = *(int*)(data->Rtex.add_image + (data->Rtex.size_line * ceil.y) + (ceil.x * sizeof(int)));	
	return (*(int*)(data->Ftex.add_image + (data->Ftex.size_line * sol.y) + (sol.x * sizeof(int))));
}

int fill_column(t_data *data)
{
	int height_proj_plane;
	int row;
	int crow;
	int val2;
	int wall_row = 0;
	char *add_opp;
	int gnagna;

	add_opp = data->image.add_image + (data->raycast.column * sizeof(int));
	height_proj_plane = floor(data->player.CST / data->raycast.dist); //REVIEW Optimisation
	double coef = (double)BLOCK_SIZE / (double)data->player.height_cam ; // coef de heigh-proj_plane
	gnagna = (double)height_proj_plane/coef;
	row = data->player.hdv - (height_proj_plane - gnagna);//REVIEW Optimisation
	crow = data->screen.size.y - row;
	if (row < 0)
	{
		wall_row = 0 - row;
		row = 0;
	}
	int h_max = data->player.hdv + gnagna;
	if (h_max > data->screen.size.y)
		h_max = data->screen.size.y;
	while (row < h_max) //REVIEW Optimisation
	{
		*(int*)(add_opp + (row * data->image.size_line)) = select_sprite_color(data, height_proj_plane, wall_row); //RGB
		row++;
		wall_row++;
	}
	//TODO faire un recap de toute les variable (surtout les alpha beta gamma)

	double val_cst[4];
	double cosB;
	cosB = cos(data->raycast.beta); 
	val_cst[0] = (data->raycast.dist / cosB);
	val_cst[1] = gnagna;
	val_cst[2] = (data->player.dist_proj_plane / cosB) * (BLOCK_SIZE - data->player.height_cam);
	val_cst[3] = (data->player.dist_proj_plane / cosB) * (data->player.height_cam);
	height_proj_plane = height_proj_plane - gnagna; //h_max - data->screen.size.y / 2;

	if (row < crow)
	{
		while (row <= data->screen.size.y)
		{
			if (row > 0)
				*(int*)(add_opp + (row * data->image.size_line)) = floor_color(data, val_cst, height_proj_plane, &val2);; 
			row++;
			if (crow <= data->screen.size.y)
			{
				*(int*)(add_opp + (data->image.size_line * (data->screen.size.y - crow))) = val2;
				crow++;
			}
			val_cst[1]++;
			height_proj_plane++;
		}
	}
	else
	{
		int val1;
		while (crow <= data->screen.size.y)
		{
			val1 = floor_color(data, val_cst, height_proj_plane, &val2);
			if (crow > 0)
				*(int*)(add_opp + (data->image.size_line * (data->screen.size.y - crow))) = val2;
			crow++;
			if (row <= data->screen.size.y)
			{
				*(int*)(add_opp + (row * data->image.size_line)) = val1; 
				row++;
			}
			val_cst[1]++;
			height_proj_plane++;
		}
	}
	return (0);
}
