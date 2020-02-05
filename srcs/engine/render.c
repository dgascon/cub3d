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

int	select_sprite_color(t_data *data, float size_div_height, int wall_row)
{
	t_coord ratio;
	
	float G;
	G = (float)data->Wtex.sizex / 64;
	ratio.y = (int)(size_div_height * wall_row) % data->Wtex.sizey;
	ratio.x = (data->raycast.face_detect == 'V') ? (int)(data->raycast.inter.y * G)  % data->Wtex.sizex : (int)(data->raycast.inter.x * G) % data->Wtex.sizex;
	return (*(int*)(data->Wtex.add_image + (data->Wtex.size_line * (int)(ratio.y)) + ((int)ratio.x * sizeof(int))));
}

int floor_color(t_data *data, float calc_const[2], int height_proj_plane, int *val2)
{
	t_coord sol;
	t_coord ceil;
	float dist_mur_sol;
	float dist_mur_plafond;
	float deltaY[2];
	float deltaX[2];
	t_f_coord sincos;

	dist_mur_plafond = calc_const[0] - (calc_const[2] / height_proj_plane);
	dist_mur_sol = calc_const[0] - (calc_const[3] / calc_const[1]);
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
			data->raycast.gamma = (data->pi.tPId) - data->raycast.alpha;
			__sincosf(data->raycast.gamma, &sincos.x, &sincos.y);
			deltaY[0] = dist_mur_sol * sincos.y * -1;
			deltaY[1] = dist_mur_plafond * sincos.y * -1;
		}
		deltaX[0] = dist_mur_sol * sincos.x;
		deltaX[1] = dist_mur_plafond * sincos.x;
	}
	else
	{
		if (data->raycast.alpha > M_PI_2 && data->raycast.alpha < data->pi.tPId)
		{
			data->raycast.gamma = M_PI - data->raycast.alpha ;
			__sincosf(data->raycast.gamma, &sincos.x, &sincos.y);
			deltaX[0] = dist_mur_sol * sincos.y;
			deltaX[1] = dist_mur_plafond * sincos.y;
		}
		else
		{
			data->raycast.gamma = data->raycast.alpha - data->pi.dPI;
			__sincosf(data->raycast.gamma, &sincos.x, &sincos.y);
			deltaX[0] = dist_mur_sol * sincos.y * -1;
			deltaX[1] = dist_mur_plafond * sincos.y * -1;
		}
		deltaY[0] = dist_mur_sol * sincos.x;
		deltaY[1] = dist_mur_plafond * sincos.x;
	}
	sol.x = (int)(data->raycast.inter.x + deltaX[0]) % data->Ftex.sizex;
	sol.y = (int)(data->raycast.inter.y + deltaY[0]) % data->Ftex.sizey;
	ceil.x = (int)(data->raycast.inter.x + deltaX[1]) % data->Rtex.sizex;
	ceil.y = (int)(data->raycast.inter.y + deltaY[1]) % data->Rtex.sizey;
	*val2 = *(int*)(data->Rtex.add_image + (data->Rtex.size_line * ceil.y) + (ceil.x * sizeof(int)));	
	return (*(int*)(data->Ftex.add_image + (data->Ftex.size_line * sol.y) + (sol.x * sizeof(int))));
}

void	print_only_ceil(t_data *data, float val_cst[4], int toto)
{
	int val2;
	char *add_opp;
	int crow = 0;

	add_opp = data->image.add_image + (data->raycast.column * sizeof(int));
	while (crow < data->screen.size.y)
	{
		floor_color(data, val_cst, toto, &val2);
		*(int*)(add_opp + (data->image.size_line * (data->screen.size.y - crow))) = val2;
		crow++;
		val_cst[1]++;
		toto++;
	}
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
	float coefcam;
	int h_max;
	float cosB;
	float val_cst[4];
	int		toto;

	add_opp = data->image.add_image + (data->raycast.column * sizeof(int));
	height_proj_plane = floorf(data->player.CST / data->raycast.dist); //REVIEW Optimisation
	coefcam = (float)BLOCK_SIZE / data->player.height_cam; // coefcam de heigh-proj_plane
	gnagna = (float)height_proj_plane/coefcam;
	toto = height_proj_plane - gnagna;
	row = data->player.hdv - toto;//REVIEW Optimisation
	crow = data->screen.size.y - row;
	if (row < 0)
	{
		wall_row = 0 - row;
		row = 0;
	}
	h_max = data->player.hdv + gnagna;
	if (h_max > data->screen.size.y)
		h_max = data->screen.size.y;
	float racourcis = (float)data->Wtex.sizey / height_proj_plane;
	while (row < h_max) //REVIEW Optimisation
	{
		*(int*)(add_opp + (row * data->image.size_line)) = select_sprite_color(data, racourcis, wall_row); //RGB
		row++;
		wall_row++;
	}
	//TODO faire un recap de toute les variable (surtout les alpha beta gamma)

	cosB = cosf(data->raycast.beta); 
	val_cst[0] = (data->raycast.dist / cosB);
	val_cst[1] = gnagna;
	val_cst[2] = (data->player.dist_proj_plane / cosB) * (BLOCK_SIZE - data->player.height_cam);
	val_cst[3] = (data->player.dist_proj_plane / cosB) * (data->player.height_cam);
	row = h_max;//permet d'avoir le sol correct quand il n'y a plus de mur 

	int val1;
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
			*(int*)(add_opp + (row * data->image.size_line)) = floor_color(data, val_cst, toto, &val2);
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
			return (0);
		}
		while (crow < data->screen.size.y)
		{
			val1 = floor_color(data, val_cst, toto, &val2);
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
	return (0);
}
